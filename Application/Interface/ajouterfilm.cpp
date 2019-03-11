#include "ajouterfilm.h"
#include "ui_ajouterfilm.h"

AjouterFilm::AjouterFilm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterFilm)
{
    ui->setupUi(this);

}

AjouterFilm::~AjouterFilm()
{
    delete ui;
}
