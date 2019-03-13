#include "ajouterfilm.h"
#include "ui_ajouterfilm.h"
#include<QDebug>
#include "film.h"
#include<QBuffer>
#include <QIntValidator>

AjouterFilm::AjouterFilm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterFilm)
{
    ui->setupUi(this);

    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(ui->buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    connect(ui->pbAjoutPhoto, SIGNAL(clicked()),this, SLOT (AjoutPhoto ()));
}

AjouterFilm::~AjouterFilm()
{
    delete ui;
}

Film AjouterFilm::validation_donnees()
{
    QValidator *validator = new QIntValidator (this);
    ui->leAjoutDuree->setValidator(validator);

    mFilm.setTitre(ui->leAjoutTitre->text());
    mFilm.setAnnee(ui->leAjoutAnnee->text().toInt());
    mFilm.setGenre(ui->leAjoutGenre->text());
    mFilm.setDuree(ui->leAjoutDuree->text().toInt());
    mFilm.setLangue(ui->leAjoutVO->text());

    // att: .h QString infoFilm = ui-> teAjoutInfo->toPlainText();
    // ? ui->labelPhoto->pixmap()->toImage());

    return mFilm;
}

void AjouterFilm::AjoutPhoto()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Image"), "c:/", tr("Image Files (*.png *.jpg *.bmp)"));
    QImage img= QImage(fileName).scaled(ui->lbAjoutAffiche->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->lbAjoutAffiche->setPixmap(QPixmap::fromImage(img));

        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        img.save(&buffer, "PNG");
        mFilm.setPhoto(byteArray);

}
