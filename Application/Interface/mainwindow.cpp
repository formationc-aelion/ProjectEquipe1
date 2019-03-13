#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include "film.h"
#include <QVariant>
#include <QSqlRecord>
#include "traitementdataFilm.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialisation(); //Initialisation de l'interface
    ModelFilmSetup();// Création et liaison à l'interface du model de film ainsi que le tri
    ModelStaffSetup();// Création et liason à l'interface du model de Staff ainsi que le tri


    QDataWidgetMapper * mapperfilm = MappingFilm( mFilmSortingModel ); // Création du Mapper pour l'interface Film

    //Connection des boutons de l'interface Film
    connect(ui->lvListeRechercheFilm->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            mapperfilm,
            SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->lvListeRechercheFilm->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            this,
            SLOT(conversion_min_en_heure()));

    connect(ui->pbInfoFilm,SIGNAL(clicked()),this,SLOT(apparition_texte()));
    connect(ui->pbMasquerFilm,SIGNAL(clicked()),this,SLOT(masquer_texte()));

    connect(ui->pbSupprimerFilm,SIGNAL(clicked()),this,SLOT(suppressionFilm()));

    connect(ui->pbAjouterFilm,SIGNAL(clicked()),this, SLOT(ajouter_Film()));
    connect(ui->pbModifierFilm,SIGNAL(clicked()),this, SLOT(modificationFilm()));
    connect(ui->pbModifOKFilm,SIGNAL(clicked()),this, SLOT(modif_pris_en_compte_Film()));
    connect(ui->pbModifierFilm,SIGNAL(clicked()),this, SLOT(demasquage_btn()));
    connect(ui->pbModifOKFilm,SIGNAL(clicked()),this, SLOT(cache_btn()));
    connect(ui->pbModifAnnulerFilm,SIGNAL(clicked()),this, SLOT(cache_btn()));
    connect(ui->pbModifAnnulerFilm,SIGNAL(clicked()),this, SLOT(annuler_la_modif_Film()));
    connect(ui->load_picFilm,SIGNAL(clicked()),this,SLOT(modification_photo_Film()));
    connect(ui->leRechercheFilm,SIGNAL(textChanged(QString)),this,SLOT(filtreRechercheFilm(QString)));

    //Connection des boutons de l'interface Staff




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::VerouillageFilm()
{
    ui->leTitreFilm->setReadOnly(true);
    ui->leAnneeFilm->setReadOnly(true);
    ui->leGenreFilm->setReadOnly(true);
    ui->leDureeFilm->setReadOnly(true);
    ui->leVOFilm->setReadOnly(true);
    ui->teInfoFilm->setReadOnly(true);
}

void MainWindow::VerouillageStaff()
{
    ui->leNomPrenom->setReadOnly(true);
    ui->leSexe->setReadOnly(true);
    ui->leProfession->setReadOnly(true);
    ui->leNationalite->setReadOnly(true);
    ui->leDateNaissance->setReadOnly(true);
    ui->teBio->setReadOnly(true);
}

void MainWindow::initialisation()
{
    //Initialisation de l'interface Film
    ui->teInfoFilm->setVisible(false);
    ui->pbMasquerFilm->setVisible(false);
    ui->pbModifOKFilm->setHidden(true);
    ui->pbModifAnnulerFilm->setHidden(true);
    ui->load_picFilm->setHidden(true);
    VerouillageFilm();

    //Initialisation de l'interface Staff
    ui->pbModifAnnulerStaff->setHidden(true);
    ui->pbModifOKStaff->setHidden(true);
    ui->load_pic_3->setHidden(true);
    VerouillageStaff();

}

void MainWindow::ModelFilmSetup()
{
    mFilmModel =CreateModelFilm(this);
    mFilmSortingModel = CreateSortingModelFilm(this , mFilmModel);

    ui->lvListeRechercheFilm->setModel(mFilmSortingModel);
    ui->lvListeRechercheFilm->setModelColumn(1);
}

void MainWindow::ModelStaffSetup()
{
    mStaffModel= CreateModelStaff(this);
    mStaffSortingModel=CreateSortingModelStaff(this,mStaffModel);

    ui->lvListeRechercheStaff->setModel(mStaffSortingModel);
    ui->lvListeRechercheStaff->setModelColumn(1);
}

void MainWindow::DeverouillageFilm()
{
    ui->leTitreFilm->setReadOnly(false);
    ui->leAnneeFilm->setReadOnly(false);
    ui->leGenreFilm->setReadOnly(false);
    ui->leDureeFilm->setReadOnly(false);
    ui->leVOFilm->setReadOnly(false);
    ui->teInfoFilm->setReadOnly(false);
}

void MainWindow::DeverouillageStaff()
{
    ui->leNomPrenom->setReadOnly(false);
    ui->leSexe->setReadOnly(false);
    ui->leProfession->setReadOnly(false);
    ui->leNationalite->setReadOnly(false);
    ui->leDateNaissance->setReadOnly(false);
    ui->teBio->setReadOnly(false);
}

int MainWindow::conversion_en_int()
{
    return Conversionint(ui->leDureeFilm->text());
}


QDataWidgetMapper* MainWindow::MappingFilm(QSortFilterProxyModel *FilmSortingModel)
{
    QDataWidgetMapper *mapperfilm = new QDataWidgetMapper;
    mapperfilm->setModel(FilmSortingModel);

    mapperfilm->addMapping(ui->leTitreFilm, 1);
    mapperfilm->addMapping(ui->leAnneeFilm, 2);
    mapperfilm->addMapping(ui->leGenreFilm, 3);
    mapperfilm->addMapping(ui->leDureeFilm, 4);
    mapperfilm->addMapping(ui->leVOFilm, 5);
    mapperfilm->addMapping(ui->lbAfficheFilm,6);
    mapperfilm->addMapping(ui->teInfoFilm, 7);
    return mapperfilm;
}

void MainWindow::ajouter_Film()
{
    AjouterFilm af; // déclaration de la boîte de dialogue affichage

    int result = af.exec();// affichage de la fenêtre d'ajout
    if(result==QDialog::DialogCode::Accepted)
    {
        Film filmAjoute = af.validation_donnees();
        this->DisplayFilm(filmAjoute);
        this->enregistrementAjoutFilm(filmAjoute);

    }
    else{}
}

void MainWindow::DisplayFilm(Film filmAjoute)
{
    ui->leTitreFilm->setText(filmAjoute.titre());
    ui->leAnneeFilm->setText(QString::number(filmAjoute.annee()));
    ui->leGenreFilm->setText(filmAjoute.genre());
    ui->leDureeFilm->setText(QString::number(filmAjoute.duree()));
    ui->leVOFilm->setText(filmAjoute.langue());
}

void MainWindow::enregistrementAjoutFilm(Film filmAjoute)
{
    AjoutFilm(filmAjoute,mFilmModel);
}



void MainWindow::conversion_min_en_heure()
{
    QString conversion_en_heure = ui->leDureeFilm->text();
    int chiffre = conversion_en_heure.toInt();
    ui->leDureeFilm->setText(ConversionMinHeure(chiffre));
    qDebug () << conversion_en_heure << "resultat apres conversion";

}

void MainWindow::apparition_texte()
{
    ui->teInfoFilm->setVisible(true);
    ui->pbMasquerFilm->setVisible(true);
    ui->pbInfoFilm->setHidden(true);

}

void MainWindow::suppressionFilm()
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



void MainWindow::modificationFilm()
{
    DeverouillageFilm();

}


void MainWindow::modif_pris_en_compte_Film()
{

    QString titre = ui->leTitreFilm->text();
    QString annee = ui->leAnneeFilm->text();
    QString genre = ui->leGenreFilm->text();
    QString duree = ui->leDureeFilm->text();
    QString vo = ui->leVOFilm->text();
    //QString resume = ui->teInfo->text();

    if (duree.contains('h', Qt::CaseInsensitive))

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

    VerouillageFilm();


}


void MainWindow::masquer_texte_Film()
{
    ui->teInfoFilm->setHidden(true);
    ui->pbMasquerFilm->setHidden(true);
    ui->pbInfoFilm->setVisible(true);
}


void MainWindow::filtreRechercheFilm(QString tri)
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

void MainWindow::annuler_la_modif_Film()
{

    mFilmModel->select();
    VerouillageFilm();
}

void MainWindow::modification_photo_Film()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "c:/", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage img= QImage(fileName).scaled(ui->lbAfficheFilm->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->lbAfficheFilm->setPixmap(QPixmap::fromImage(img));
}

