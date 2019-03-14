#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include "film.h"
#include <QVariant>
#include <QSqlRecord>
#include<QSqlQuery>
#include "traitementdataFilm.h"
#include "traitementdatestaff.h"
#include "traitementdatastatistique.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initialisation(); //Initialisation de l'interface
    ModelFilmSetup();// Création et liaison à l'interface du model de film ainsi que le tri
    ModelStaffSetup();// Création et liason à l'interface du model de Staff ainsi que le tri

    QDataWidgetMapper * mapperfilm = MappingFilm( mFilmSortingModel ); // Création du Mapper pour l'interface Film
    QDataWidgetMapper * mapperstaff = MappingStaff( mStaffSortingModel ); // Création du Mapper pour l'interface Realisateur

    //creation label Combobox
    fillCbGenre(ui->cbGenreFilm);
    fillCbGenre(ui->cbGenreStat);


    //Connection des boutons de l'interface Film
    connect(ui->lvListeRechercheFilm->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            mapperfilm,SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->lvListeRechercheFilm->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            this,SLOT(image_loading_Film(QModelIndex)));

    connect(ui->lvListeRechercheFilm->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            this,SLOT(conversion_min_en_heure()));

    connect(ui->pbSupprimerFilm,SIGNAL(clicked()),this,SLOT(suppressionFilm()));

    connect(ui->pbAjouterFilm,SIGNAL(clicked()),this, SLOT(ajouter_Film()));
    connect(ui->pbModifierFilm,SIGNAL(clicked()),this, SLOT(modificationFilm()));
    connect(ui->pbModifOKFilm,SIGNAL(clicked()),this, SLOT(modif_pris_en_compte_Film()));
    connect(ui->pbModifierFilm,SIGNAL(clicked()),this, SLOT(demasquage_btn()));
    connect(ui->pbModifOKFilm,SIGNAL(clicked()),this, SLOT(cache_btn()));
    connect(ui->pbModifAnnulerFilm,SIGNAL(clicked()),this, SLOT(cache_btn()));
    connect(ui->pbModifAnnulerFilm,SIGNAL(clicked()),this, SLOT(annuler_la_modif_Film()));
    connect(ui->pbload_picFilm,SIGNAL(clicked()),this,SLOT(modification_photo_Film()));
    connect(ui->leRechercheFilm,SIGNAL(textChanged(QString)),this,SLOT(filtreRechercheFilm(QString)));

    connect(ui->pbInfoFilm,SIGNAL(clicked()),this,SLOT(apparition_texte()));
    connect(ui->pbMasquerFilm,SIGNAL(clicked()),this,SLOT(masquer_texte_Film()));


    //Connection des boutons de l'interface Staff

    connect(ui->lvListeRechercheStaff->selectionModel(), SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            mapperstaff,
            SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->lvListeRechercheStaff->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            this,SLOT(image_loading_Staff(QModelIndex))); // fonction image loading pour réalisateur à rajouter

    connect(ui->lvListeRechercheStaff->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
                this,SLOT(liaisonFilmReal(QModelIndex)));


    connect(ui->pbSupprimerStaff,SIGNAL(clicked()),SLOT(suppressionStaff()));
    connect(ui->pbAjouterStaff, SIGNAL(clicked()),this, SLOT(ajouter_Staff()));
    connect(ui->pbModifierStaff,SIGNAL(clicked()),this, SLOT(modificationStaff()));
    connect(ui->pbModifOKStaff,SIGNAL(clicked()),this, SLOT(modif_pris_en_compte_Staff()));
    connect(ui->pbModifierStaff,SIGNAL(clicked()),this, SLOT(demasquage_btnStaff()));
    connect(ui->pbModifOKStaff,SIGNAL(clicked()),this, SLOT(cache_btnStaff()));
    connect(ui->pbModifAnnulerFilm,SIGNAL(clicked()),this, SLOT(cache_btnStaff()));
    connect(ui->pbModifAnnulerStaff,SIGNAL(clicked()),this, SLOT(annuler_la_modif_Staff()));
    connect(ui->pbload_pic_staff,SIGNAL(clicked()),this,SLOT(modification_photo_Staff()));

    connect(ui->leRechercheStaff,SIGNAL(textChanged(QString)),this,SLOT(filtreRechercheStaff(QString)));
    connect(ui->lvListeRechercheStaff->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            mapperstaff,SLOT(setCurrentModelIndex(QModelIndex)));

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
    ui->deDateNaissance->setReadOnly(true);
    ui->leNationalite->setReadOnly(true);
    ui->leNationaliteB->setReadOnly(true);
    ui->leProfessionA->setReadOnly(true);
    ui->leProfessionB->setReadOnly(true);
    ui->leProfessionC->setReadOnly(true);
    ui->teBio->setReadOnly(true);
}

void MainWindow::initialisation()
{
    //Initialisation de l'interface Film
    ui->teInfoFilm->setVisible(false);
    ui->pbMasquerFilm->setVisible(false);
    ui->pbModifOKFilm->setHidden(true);
    ui->pbModifAnnulerFilm->setHidden(true);
    ui->pbload_picFilm->setHidden(true);
    VerouillageFilm();

    //Initialisation de l'interface Staff
    ui->pbModifAnnulerStaff->setHidden(true);
    ui->pbModifOKStaff->setHidden(true);
    ui->pbload_pic_staff->setHidden(true);
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
    ui->deDateNaissance->setReadOnly(false);
    ui->leNationalite->setReadOnly(false);
    ui->leNationaliteB->setReadOnly(false);
    ui->leProfessionA->setReadOnly(false);
    ui->leProfessionB->setReadOnly(false);
    ui->leProfessionC->setReadOnly(false);
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
    mapperfilm->addMapping(ui->teInfoFilm, 7);
    return mapperfilm;
}

QDataWidgetMapper* MainWindow::MappingStaff(QSortFilterProxyModel *StaffSortingModel)
{
    QDataWidgetMapper *mapperstaff = new QDataWidgetMapper;
    mapperstaff->setModel(StaffSortingModel);

    mapperstaff->addMapping(ui->leNomPrenom, 1);
    mapperstaff->addMapping(ui->deDateNaissance, 2);
    mapperstaff->addMapping(ui->leNationalite, 3);
    mapperstaff->addMapping(ui->leNationaliteB, 4);
    mapperstaff->addMapping(ui->leProfessionA, 5);
    mapperstaff->addMapping(ui->leProfessionB, 6);
    mapperstaff->addMapping(ui->leProfessionC, 7);
    mapperstaff->addMapping(ui->teBio, 9);
    return mapperstaff;
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

void MainWindow::ajouter_Staff()
{
    Staff staffAjoute = validation_donneesStaff();
    this->DisplayStaff(staffAjoute);
    this->enregistrementAjoutStaff(staffAjoute);
}



void MainWindow::DisplayFilm(Film filmAjoute)
{
    ui->leTitreFilm->setText(filmAjoute.titre());
    ui->leAnneeFilm->setText(QString::number(filmAjoute.annee()));
    ui->leGenreFilm->setText(filmAjoute.genre());
    ui->leDureeFilm->setText(QString::number(filmAjoute.duree()));
    ui->leVOFilm->setText(filmAjoute.langue());
}

void MainWindow::DisplayStaff(Staff staffAjoute)
{
    ui->leNomPrenom->setText(staffAjoute.nom());
    ui->deDateNaissance->setDate(staffAjoute.dateNaissance());
    ui->leNationalite->setText(staffAjoute.nationaliteA());
    ui->leNationaliteB->setText(staffAjoute.nationaliteB());
    ui->leProfessionA->setText(staffAjoute.professionA());
    ui->leProfessionB->setText(staffAjoute.professionB());
    ui->leProfessionC->setText(staffAjoute.professionB());
    //ui->load_pic_3->setpixmap(staffAjoute.photo());
    ui->teBio->setText(staffAjoute.bio());
}

Staff MainWindow::validation_donneesStaff()
{
    mStaff.setNom(ui->leNomPrenom->text());
    mStaff.setDateNaissance(ui->deDateNaissance->date());
    mStaff.setNationaliteA(ui->leNationalite->text());
    mStaff.setNationaliteB(ui->leNationaliteB->text());
    mStaff.setProfessionA(ui->leProfessionA->text());
    mStaff.setProfessionB(ui->leProfessionB->text());
    mStaff.setProfessionC(ui->leProfessionC->text());
    mStaff.setBio(ui->teBio->toPlainText());

    return mStaff;
}

void MainWindow::enregistrementAjoutFilm(Film filmAjoute)
{
    AjoutFilm(filmAjoute,mFilmModel);
}

void MainWindow::enregistrementAjoutStaff(Staff staffAjoute)
{
    AjoutStaff(staffAjoute,mStaffModel);
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
        DeleteFilm(mFilmSortingModel,a_supprimer,mFilmModel);

        ui->leTitreFilm->clear();
        ui->leAnneeFilm->clear();
        ui->leGenreFilm->clear();
        ui->leDureeFilm->clear();
        ui->leVOFilm->clear();
        ui->teInfoFilm->clear();

        mFilmModel->submitAll();
        mFilmModel->select();
    }
}

void MainWindow::suppressionStaff()
{
    int response = QMessageBox::critical(this,"Supprimer le fichier","Voulez-vous vraiment supprimer cette entrée de façon permanente?",
                                         QMessageBox::Yes | QMessageBox::No);
    if (response == QMessageBox::Yes)
    {
        QModelIndex a_supprimer = ui->lvListeRechercheStaff->currentIndex();
        DeleteStaff(mStaffSortingModel,a_supprimer,mStaffModel);
        QMessageBox::information(this,"Suppression","Element supprimé");
        ui->leNomPrenom->clear();
        ui->deDateNaissance->clear();
        ui->leNationalite->clear();
        ui->leNationaliteB->clear();
        ui->leProfessionA->clear();
        ui->leProfessionB->clear();
        ui->leProfessionC->clear();
        ui->lbAffiche_Staff->clear();
        ui->teBio->clear();

        mStaffModel->submitAll();
        mStaffModel->select();
    }
}


void MainWindow::modificationFilm()
{
    DeverouillageFilm();
}

void MainWindow::modificationStaff()
{
    DeverouillageStaff();
}


void MainWindow::modif_pris_en_compte_Film()
{
    QModelIndex a_modifier = ui->lvListeRechercheFilm->currentIndex();
    QString titre = ui->leTitreFilm->text();
    QString anneestring = ui->leAnneeFilm->text();
    int annee=anneestring.toInt();
    QString genre = ui->leGenreFilm->text();
    QString duree = ui->leDureeFilm->text();
    QString vo = ui->leVOFilm->text();
    QString resume = ui->teInfoFilm->toPlainText();
    QPixmap const *imageaModifier= ui->lbAfficheFilm->pixmap() ;
    QByteArray imgByteArr= photoPixMaptoBytearray(imageaModifier);
    if (duree.contains('h', Qt::CaseInsensitive))
    {
        int a = conversion_en_int();
        duree = QString("%1")
                .arg(a);
    }
    Film Filmtemp (titre,genre,vo,annee,duree.toInt(), imgByteArr ,resume);
    modificationfilm(Filmtemp,mFilmModel,mFilmSortingModel,a_modifier);

    VerouillageFilm();
}

void MainWindow::modif_pris_en_compte_Staff()
{
    QString nom = ui->leNomPrenom->text();
    QDate dateNaissance = ui->deDateNaissance->date();
    QString nationaliteA = ui->leNationalite->text();
    QString nationaliteB = ui->leNationaliteB->text();
    QString professionA = ui->leProfessionA->text();
    QString professionB = ui->leProfessionB->text();
    QString professionC = ui->leProfessionC->text();
    QPixmap const *imageaModifier= ui->lbAffiche_Staff->pixmap() ;
    QByteArray imgByteArr= photoPixMaptoBytearray(imageaModifier);
    QString bio = ui->teBio->toPlainText();

    Staff Stafftemp (nom,dateNaissance,nationaliteA,nationaliteB,professionA, professionB, professionC, imgByteArr, bio);
    QModelIndex a_modifier = ui->lvListeRechercheStaff->currentIndex();
    modificationstaff(Stafftemp,mStaffModel,mStaffSortingModel,a_modifier);
    // modification_photo_Staff();
    VerouillageStaff();
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

void MainWindow::filtreRechercheStaff(QString tri)
{
    QString find ="*"+tri+"*";

    mStaffSortingModel->setFilterWildcard(find);
    mStaffSortingModel->setFilterKeyColumn(1);
}

void MainWindow::demasquage_btn()
{
    ui->pbModifierFilm->setHidden(true);
    ui->pbModifOKFilm->setHidden(false);
    ui->pbModifAnnulerFilm->setHidden(false);
    ui->pbload_picFilm->setHidden(false);

}

void MainWindow::demasquage_btnStaff()
{
    ui->pbModifierStaff->setHidden(true);
    ui->pbModifOKStaff->setHidden(false);
    ui->pbModifAnnulerStaff->setHidden(false);
    ui->pbload_pic_staff->setHidden(false);
}

void MainWindow::cache_btn()
{
    ui->pbModifOKFilm->setHidden(true);
    ui->pbModifAnnulerFilm->setHidden(true);
    ui->pbload_picFilm->setHidden(true);
    ui->pbModifierFilm->setHidden(false);
}

void MainWindow::cache_btnStaff()
{

    ui->pbModifOKStaff->setHidden(true);
    ui->pbModifAnnulerStaff->setHidden(true);
    ui->pbload_pic_staff->setHidden(true);
    ui->pbModifierStaff->setHidden(false);
}

void MainWindow::annuler_la_modif_Film()
{
    mFilmModel->select();
    VerouillageFilm();
}

void MainWindow::annuler_la_modif_Staff()
{
    mStaffModel->select();
    VerouillageStaff();
}

void MainWindow::modification_photo_Film()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "c:/", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage img= QImage(fileName).scaled(ui->lbAfficheFilm->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->lbAfficheFilm->setPixmap(QPixmap::fromImage(img));

}

void MainWindow::modification_photo_Staff()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "c:/", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage img= QImage(fileName).scaled(ui->lbAffiche_Staff->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->lbAffiche_Staff->setPixmap(QPixmap::fromImage(img));
}

Staff MainWindow::staff() const
{
    return mStaff;
}


void MainWindow::image_loading_Film(QModelIndex indexselected)
{
    QPixmap PhotoPix=photobytearraytoPixmap(mFilmSortingModel,indexselected);

    ui->lbAfficheFilm->setPixmap(PhotoPix);//affichage de la QPixmap
}

void MainWindow::image_loading_Staff(QModelIndex indexselected)
{
    QPixmap PhotoPix=photobytearraytoPixmap(mStaffSortingModel,indexselected);

    ui->lbAffiche_Staff->setPixmap(PhotoPix);//affichage de la QPixmap

}

    void MainWindow:: liaisonFilmReal(QModelIndex indexRealisateur)
    {
       QSqlDatabase db = QSqlDatabase::database("connexionBDDfilm");
       QVariant indexreal = mStaffSortingModel->data(mStaffSortingModel->index(indexRealisateur.row(),0));
       qDebug ()<<indexreal;
       int index = indexreal.toInt();
        qDebug ()<<index;


        QSqlQuery filmo (db);
        QString realisateur = ui->leNomPrenom->text();
        filmo.prepare("SELECT film.fi_titre, film.fi_date_sortie, film.fi_genre FROM staff JOIN film ON staff.id_staff = film.id_real WHERE id_staff = :index ");
        filmo.bindValue(":index",index);
        filmo.exec();

        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(filmo);
        model->setHeaderData(0, Qt::Horizontal, tr("Titre"));
        model->setHeaderData(1, Qt::Horizontal, tr("Année"));
        model->setHeaderData(2, Qt::Horizontal, tr("Genre"));
        ui->tvFilmo->setModel(model);
        ui->tvFilmo->show();

    }


