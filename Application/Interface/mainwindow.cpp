#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
