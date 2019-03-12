#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include "film.h"
#include <QVariant>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Verouillage();
    ui->teInfoFilm->setVisible(false);
    ui->pbMasquerFilm->setVisible(false);

    ui->pbModifOKFilm->setHidden(true);
    ui->pbModifAnnulerFilm->setHidden(true);
    ui->load_picFilm->setHidden(true);

    QSqlDatabase db = QSqlDatabase::database("connexionBDDfilm");
    mFilmModel = new QSqlTableModel (this,db);
    mFilmModel->setTable("film");
    mFilmModel->select();
    mFilmModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    mFilmSortingModel = new QSortFilterProxyModel(this);
    mFilmSortingModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mFilmSortingModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    mFilmSortingModel->sort(1, Qt::AscendingOrder);
    mFilmSortingModel->setDynamicSortFilter(true);
    mFilmSortingModel->setSourceModel(mFilmModel);


    ui->lvListeRechercheFilm->setModel(mFilmSortingModel);
    ui->lvListeRechercheFilm->setModelColumn(1);

    QSqlDatabase dbstaff = QSqlDatabase::database("connexionBDDStaff");
    mStaffModel = new QSqlTableModel (this,dbstaff);
    mStaffModel->setTable("Staff");
    mStaffModel->select();
    mStaffModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

    mStaffSortingModel = new QSortFilterProxyModel(this);
    mStaffSortingModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mStaffSortingModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    mStaffSortingModel->sort(1, Qt::AscendingOrder);
    mStaffSortingModel->setDynamicSortFilter(true);
    mStaffSortingModel->setSourceModel(mStaffModel);


    ui->lvListeRechercheStaff->setModel(mStaffSortingModel);
    ui->lvListeRechercheStaff->setModelColumn(1);




    QDataWidgetMapper *mapperfilm = new QDataWidgetMapper;
    mapperfilm->setModel(mFilmSortingModel);

    mapperfilm->addMapping(ui->leTitreFilm, 1);
    mapperfilm->addMapping(ui->leAnneeFilm, 2);
    mapperfilm->addMapping(ui->leGenreFilm, 3);
    mapperfilm->addMapping(ui->leDureeFilm, 4);
    mapperfilm->addMapping(ui->leVOFilm, 5);
    mapperfilm->addMapping(ui->lbAfficheFilm,6);
    mapperfilm->addMapping(ui->teInfoFilm, 7);


    connect(ui->lvListeRechercheFilm->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            mapperfilm,
            SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->lvListeRechercheFilm->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            this,
            SLOT(conversion_min_en_heure()));

    connect(ui->pbInfoFilm,SIGNAL(clicked()),this,SLOT(apparition_texte()));
    connect(ui->pbMasquerFilm,SIGNAL(clicked()),this,SLOT(masquer_texte()));

    connect(ui->pbSupprimerFilm,SIGNAL(clicked()),this,SLOT(suppression()));

    connect(ui->pbAjouterFilm,SIGNAL(clicked()),this, SLOT(ajouter_Film()));
    connect(ui->pbModifierFilm,SIGNAL(clicked()),this, SLOT(modification()));
    connect(ui->pbModifOKFilm,SIGNAL(clicked()),this, SLOT(modif_pris_en_compte()));
    connect(ui->pbModifierFilm,SIGNAL(clicked()),this, SLOT(demasquage_btn()));
    connect(ui->pbModifOKFilm,SIGNAL(clicked()),this, SLOT(cache_btn()));
    connect(ui->pbModifAnnulerFilm,SIGNAL(clicked()),this, SLOT(cache_btn()));
    connect(ui->pbModifAnnulerFilm,SIGNAL(clicked()),this, SLOT(annuler_la_modif()));
    connect(ui->load_picFilm,SIGNAL(clicked()),this,SLOT(modification_photo()));

    connect(ui->leRechercheFilm,SIGNAL(textChanged(QString)),this,SLOT(filtreRecherche(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Verouillage()
{
    ui->leTitreFilm->setReadOnly(true);
    ui->leAnneeFilm->setReadOnly(true);
    ui->leGenreFilm->setReadOnly(true);
    ui->leDureeFilm->setReadOnly(true);
    ui->leVOFilm->setReadOnly(true);
    ui->teInfoFilm->setReadOnly(true);
}

void MainWindow::Deverouillage()
{
    ui->leTitreFilm->setReadOnly(false);
    ui->leAnneeFilm->setReadOnly(false);
    ui->leGenreFilm->setReadOnly(false);
    ui->leDureeFilm->setReadOnly(false);
    ui->leVOFilm->setReadOnly(false);
    ui->teInfoFilm->setReadOnly(false);
}

int MainWindow::conversion_en_int()
{
    QString conversion_galere = ui->leDureeFilm->text();

    //CaseInsensitive gere h et H et aussi min et MIN
    //fct contains me renvoi un bool
    bool contient_h = conversion_galere.contains('h', Qt::CaseInsensitive);
    bool contient_min = conversion_galere.contains("min", Qt::CaseInsensitive);

    if (contient_h == 1 && contient_min == 1)
    {

        QStringList list1 = conversion_galere.split('h',QString::SkipEmptyParts);
        list1[1] = list1[1].remove("min");
        list1[1] = list1[1].left(2);
        QString element_heure = list1.at(0);
        int heure = element_heure.toInt();
        heure *= 60;
        QString element_minutes = list1.at(1);
        int minutes = element_minutes.toInt();
        int resultat = heure + minutes;
        qDebug()<< resultat;
        return heure + minutes;

    }
    else if (contient_h == 0 && contient_min == 1)
    {
        QString element_minutes = conversion_galere.left(2);
        int minutes = element_minutes.toInt();
        qDebug()<< minutes;
        return minutes;
    }

    else if (contient_h == 1 && contient_min == 0)

    {
        QString element_heure = conversion_galere.left(1);
        int heure = element_heure.toInt();
        heure *= 60;
        qDebug()<< heure;

        return heure;

    }

    else
    {
        int a = 0;
        return a;
    }

}

void MainWindow::DisplayFilm(Film filmAjoute)
{
    ui->leTitreFilm->setText(filmAjoute.titre());
    ui->leAnneeFilm->setText(QString::number(filmAjoute.annee()));
    ui->leGenreFilm->setText(filmAjoute.genre());
    ui->leDureeFilm->setText(QString::number(filmAjoute.duree()));
    ui->leVOFilm->setText(filmAjoute.langue());
}

void MainWindow::ajouter_Film()
{
    AjouterFilm af; // déclaration de la boîte de dialogue affichage

    int result = af.exec();// affichage de la fenêtre d'ajout
    if(result==QDialog::DialogCode::Accepted)
    {
        Film filmAjoute = af.validation_donnees();
        this->DisplayFilm(filmAjoute);
        this->enregistrementAjout();

    }
    else{}
}

void MainWindow::enregistrementAjout()
{
    mFilmModel->insertRow(mFilmModel->rowCount());
    int lastrow=mFilmModel->rowCount()-1;

    mFilmModel->setData(mFilmModel->index(lastrow,1),ui->leTitreFilm->text());
    mFilmModel->setData(mFilmModel->index(lastrow,2),ui->leAnneeFilm->text());
    mFilmModel->setData(mFilmModel->index(lastrow,3),ui->leGenreFilm->text());
    mFilmModel->setData(mFilmModel->index(lastrow,4),ui->leDureeFilm->text());
    mFilmModel->setData(mFilmModel->index(lastrow,5),ui->leVOFilm->text());

    mFilmModel->submitAll();
}



void MainWindow::conversion_min_en_heure()
{
    QString conversion_en_heure = ui->leDureeFilm->text();
    int chiffre = conversion_en_heure.toInt();

    qDebug () << chiffre;

    if (chiffre == 60)
    {
        conversion_en_heure = "1h";
        qDebug () << conversion_en_heure <<"condition 1h";
    }
    else if (chiffre > 60)
    {
        int a = conversion_en_heure.toInt();
        int resultat = a/60;
        int modulo = a%60;
        char heure = 'h';
        QString minutes = "min";;
        QString modulo_avec_zero = QString ("%1")
                .arg(modulo);

        if (modulo < 10)

        { modulo_avec_zero = QString("%1%2")
                    .arg("0")
                    .arg(modulo);
            qDebug () << modulo_avec_zero << "condition ou module<10";
        }


        conversion_en_heure = QString ("%1%2%3")
                .arg(resultat)
                .arg(heure)
                .arg(modulo_avec_zero);
        qDebug () << conversion_en_heure << "condition 1het qques min";
    }
    /*else {
        conversion_en_heure += "min";
        qDebug () << conversion_en_heure << "condition min";
    }*/

    ui->leDureeFilm->setText(conversion_en_heure);
    qDebug () << conversion_en_heure << "resultat apres conversion";


}

void MainWindow::apparition_texte()
{
    ui->teInfoFilm->setVisible(true);
    ui->pbMasquerFilm->setVisible(true);
    ui->pbInfoFilm->setHidden(true);

}

void MainWindow::suppression()
{

    int response = QMessageBox::critical(this,"Supprimer le fichier","Voulez-vous vraiment supprimer cette entrée de façon permanente?",
                                         QMessageBox::Yes | QMessageBox::No);
    if (response == QMessageBox::Yes)
    {
        QModelIndex a_supprimer = ui->lvListeRechercheFilm->currentIndex();
        mFilmSortingModel->removeRow(a_supprimer.row());
        ui->leTitreFilm->clear();
        ui->leAnneeFilm->clear();
        ui->leGenreFilm->clear();
        ui->leDureeFilm->clear();
        ui->leVOFilm->clear();
        ui->teInfoFilm->clear();


        QMessageBox::information(this,"Suppression","Element supprimé");

    }
    mFilmModel->submitAll();
    mFilmModel->select();

}



void MainWindow::modification()
{
    Deverouillage();

}


void MainWindow::modif_pris_en_compte()
{

    QString titre = ui->leTitreFilm->text();
    QString annee = ui->leAnneeFilm->text();
    QString genre = ui->leGenreFilm->text();
    QString duree = ui->leDureeFilm->text();
    QString vo = ui->leVOFilm->text();
    //QString resume = ui->teInfo->text();

    if (duree.contains('h', Qt::CaseInsensitive) || duree.contains("min", Qt::CaseInsensitive))

    {
        int a = conversion_en_int();
        duree = QString("%1")
                .arg(a);
    }


    ui->leTitreFilm->setText(titre);
    ui->leAnneeFilm->setText(annee);
    ui->leGenreFilm->setText(genre);
    ui->leDureeFilm->setText(duree);
    ui->leVOFilm->setText(vo);


    mFilmModel->submitAll();

    this->conversion_min_en_heure();

    Verouillage();


}


void MainWindow::masquer_texte()
{
    ui->teInfoFilm->setHidden(true);
    ui->pbMasquerFilm->setHidden(true);
    ui->pbInfoFilm->setVisible(true);
}


void MainWindow::filtreRecherche(QString tri)
{
    QString find ="*"+tri+"*";


    mFilmSortingModel->setFilterWildcard(find);
    mFilmSortingModel->setFilterKeyColumn(1);
}

void MainWindow::demasquage_btn()
{
    ui->pbModifOKFilm->setHidden(false);
    ui->pbModifAnnulerFilm->setHidden(false);
    ui->load_picFilm->setHidden(false);

}

void MainWindow::cache_btn()
{
    ui->pbModifOKFilm->setHidden(true);
    ui->pbModifAnnulerFilm->setHidden(true);
    ui->load_picFilm->setHidden(true);
}

void MainWindow::annuler_la_modif()
{

    mFilmModel->select();

    Verouillage();
}

void MainWindow::modification_photo()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "c:/", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage img= QImage(fileName).scaled(ui->lbAfficheFilm->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->lbAfficheFilm->setPixmap(QPixmap::fromImage(img));
}

