#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    QSqlDatabase db = QSqlDatabase::database("connexionBDDfilm");
        mFilmModel = new QSqlTableModel (this,db);
        mFilmModel->setTable("film");
        mFilmModel->select();


        ui->lvListeRecherche->setModel(mFilmModel);
        ui->lvListeRecherche->setModelColumn(1);

    QDataWidgetMapper *mapper = new QDataWidgetMapper;
        mapper->setModel(mFilmModel);
        mapper->addMapping(ui->leTitre, 1);
        mapper->addMapping(ui->leAnnee, 2);
        mapper->addMapping(ui->leGenre, 3);
        mapper->addMapping(ui->leDuree, 4);
        mapper->addMapping(ui->leVO, 5);

           connect(ui->lvListeRecherche->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
                mapper,
                SLOT(setCurrentModelIndex(QModelIndex)));


    connect(ui->pbAjouter,SIGNAL(clicked()),this, SLOT(ajouter_Film()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ajouter_Film()
{
    AjouterFilm af; // déclaration de la boîte de dialogue affichage
    af.exec(); // affichage de la fenêtre d'ajout
    //cf HUGO Film film = af.getDetails(); // stockage des info dans un objet film

}
