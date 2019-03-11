#include "ajouterfilm.h"
#include "ui_ajouterfilm.h"
#include<QDebug>
#include "film.h"

AjouterFilm::AjouterFilm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterFilm)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

AjouterFilm::~AjouterFilm()
{
    delete ui;
}

Film AjouterFilm::entree_donnees()
{
    Film film;
    film.setTitre(ui->leAjoutTitre->text());
    film.setAnnee(ui->leAjoutAnnee->text().toInt());
    film.setGenre(ui->leAjoutGenre->text());
    film.setDuree(ui->leAjoutDuree->text().toInt());
    film.setLangue(ui->leAjoutVO->text());
    // ? QString infoFilm = ui-> teAjoutInfo->toPlainText();
    // ? ui->labelPhoto->pixmap()->toImage());
    return film;
}

void AjouterFilm::AjoutPhoto()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "c:/", tr("Image Files (*.png *.jpg *.bmp)"));
        QImage img= QImage(fileName).scaled(ui->lbAjoutAffiche->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
        ui->lbAjoutAffiche->setPixmap(QPixmap::fromImage(img));
}
