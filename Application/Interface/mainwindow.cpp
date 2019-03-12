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
    ui->teInfo->setVisible(false);
    ui->pbMasquer->setVisible(false);

    ui->pbModifOK->setHidden(true);
    ui->pbModifAnnuler->setHidden(true);
    ui->load_pic->setHidden(true);

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


    ui->lvListeRecherche->setModel(mFilmSortingModel);
    ui->lvListeRecherche->setModelColumn(1);



    QDataWidgetMapper *mapper = new QDataWidgetMapper;
    mapper->setModel(mFilmSortingModel);

    mapper->addMapping(ui->leTitre, 1);
    mapper->addMapping(ui->leAnnee, 2);
    mapper->addMapping(ui->leGenre, 3);
    mapper->addMapping(ui->leDuree, 4);
    mapper->addMapping(ui->leVO, 5);
    mapper->addMapping(ui->lbAffiche,6);
    mapper->addMapping(ui->teInfo, 7);



   connect(ui->lvListeRecherche->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            mapper,
            SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->lvListeRecherche->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            this,
            SLOT(conversion_min_en_heure()));

    ui->lvListeRecherche->setCurrentIndex(mFilmSortingModel->index(0,1));

    connect(ui->pbInfo,SIGNAL(clicked()),this,SLOT(apparition_texte()));
    connect(ui->pbMasquer,SIGNAL(clicked()),this,SLOT(masquer_texte()));

    connect(ui->pbSupprimer,SIGNAL(clicked()),this,SLOT(suppression()));

    connect(ui->pbAjouter,SIGNAL(clicked()),this, SLOT(ajouter_Film()));
    connect(ui->pbModifier,SIGNAL(clicked()),this, SLOT(modification()));
    connect(ui->pbModifOK,SIGNAL(clicked()),this, SLOT(modif_pris_en_compte()));
    connect(ui->pbModifier,SIGNAL(clicked()),this, SLOT(demasquage_btn()));
    connect(ui->pbModifOK,SIGNAL(clicked()),this, SLOT(cache_btn()));
    connect(ui->pbModifAnnuler,SIGNAL(clicked()),this, SLOT(cache_btn()));
    connect(ui->pbModifAnnuler,SIGNAL(clicked()),this, SLOT(annuler_la_modif()));
    connect(ui->load_pic,SIGNAL(clicked()),this,SLOT(modification_photo()));

    connect(ui->leRecherche,SIGNAL(textChanged(QString)),this,SLOT(filtreRecherche(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Verouillage()
{
    ui->leTitre->setReadOnly(true);
    ui->leAnnee->setReadOnly(true);
    ui->leGenre->setReadOnly(true);
    ui->leDuree->setReadOnly(true);
    ui->leVO->setReadOnly(true);
    ui->teInfo->setReadOnly(true);
}

void MainWindow::Deverouillage()
{
    ui->leTitre->setReadOnly(false);
    ui->leAnnee->setReadOnly(false);
    ui->leGenre->setReadOnly(false);
    ui->leDuree->setReadOnly(false);
    ui->leVO->setReadOnly(false);
    ui->teInfo->setReadOnly(false);
}

int MainWindow::conversion_en_int()
{
    QString conversion_galere = ui->leDuree->text();

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
    ui->leTitre->setText(filmAjoute.titre());
    ui->leAnnee->setText(QString::number(filmAjoute.annee()));
    ui->leGenre->setText(filmAjoute.genre());
    ui->leDuree->setText(QString::number(filmAjoute.duree()));
    ui->leVO->setText(filmAjoute.langue());
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

    mFilmModel->setData(mFilmModel->index(lastrow,1),ui->leTitre->text());
    mFilmModel->setData(mFilmModel->index(lastrow,2),ui->leAnnee->text());
    mFilmModel->setData(mFilmModel->index(lastrow,3),ui->leGenre->text());
    mFilmModel->setData(mFilmModel->index(lastrow,4),ui->leDuree->text());
    mFilmModel->setData(mFilmModel->index(lastrow,5),ui->leVO->text());

    mFilmModel->submitAll();
}



void MainWindow::conversion_min_en_heure()
{
    QString conversion_en_heure = ui->leDuree->text();
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

    ui->leDuree->setText(conversion_en_heure);
    qDebug () << conversion_en_heure << "resultat apres conversion";


}

void MainWindow::apparition_texte()
{
    ui->teInfo->setVisible(true);
    ui->pbMasquer->setVisible(true);
    ui->pbInfo->setHidden(true);

}

void MainWindow::suppression()
{

<<<<<<< HEAD
   int response = QMessageBox::critical(this,"Supprimer le fichier","Voulez-vous vraiment supprimer cette entrée de façon permanente?",
                         QMessageBox::Yes | QMessageBox::No);
   if (response == QMessageBox::Yes)
   {
       QModelIndex a_supprimer = ui->lvListeRecherche->currentIndex();

       mFilmSortingModel->removeRow(a_supprimer.row());
       ui->leTitre->clear();
       ui->leAnnee->clear();
       ui->leGenre->clear();
       ui->leDuree->clear();
       ui->leVO->clear();
       ui->teInfo->clear();
=======
    int response = QMessageBox::critical(this,"Supprimer le fichier","Voulez-vous vraiment supprimer cette entrée de façon permanente?",
                                         QMessageBox::Yes | QMessageBox::No);
    if (response == QMessageBox::Yes)
    {
        QModelIndex a_supprimer = ui->lvListeRecherche->currentIndex();
        mFilmSortingModel->removeRow(a_supprimer.row());
        ui->leTitre->clear();
        ui->leAnnee->clear();
        ui->leGenre->clear();
        ui->leDuree->clear();
        ui->leVO->clear();
        ui->teInfo->clear();
>>>>>>> b421ae89664df0f65eb9189751df5491ed3fecc7


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

    QString titre = ui->leTitre->text();
    QString annee = ui->leAnnee->text();
    QString genre = ui->leGenre->text();
    QString duree = ui->leDuree->text();
    QString vo = ui->leVO->text();
    //QString resume = ui->teInfo->text();

    if (duree.contains('h', Qt::CaseInsensitive) || duree.contains("min", Qt::CaseInsensitive))

    {
        int a = conversion_en_int();
        duree = QString("%1")
                .arg(a);
    }


    ui->leTitre->setText(titre);
    ui->leAnnee->setText(annee);
    ui->leGenre->setText(genre);
    ui->leDuree->setText(duree);
    ui->leVO->setText(vo);


    mFilmModel->submitAll();

    this->conversion_min_en_heure();

    Verouillage();


}


void MainWindow::masquer_texte()
{
    ui->teInfo->setHidden(true);
    ui->pbMasquer->setHidden(true);
    ui->pbInfo->setVisible(true);
}


void MainWindow::filtreRecherche(QString tri)
{
    QString find ="*"+tri+"*";


    mFilmSortingModel->setFilterWildcard(find);
    mFilmSortingModel->setFilterKeyColumn(1);
}

void MainWindow::demasquage_btn()
{
    ui->pbModifOK->setHidden(false);
    ui->pbModifAnnuler->setHidden(false);
    ui->load_pic->setHidden(false);

}

void MainWindow::cache_btn()
{
    ui->pbModifOK->setHidden(true);
    ui->pbModifAnnuler->setHidden(true);
    ui->load_pic->setHidden(true);
}

void MainWindow::annuler_la_modif()
{

    mFilmModel->select();

    Verouillage();
}

void MainWindow::modification_photo()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "c:/", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage img= QImage(fileName).scaled(ui->lbAffiche->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->lbAffiche->setPixmap(QPixmap::fromImage(img));
}

