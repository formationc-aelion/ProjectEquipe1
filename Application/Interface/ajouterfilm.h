#ifndef AJOUTERFILM_H
#define AJOUTERFILM_H

#include <QDialog>
#include<QFileDialog>
#include <film.h>

namespace Ui {
class AjouterFilm;
}

class AjouterFilm : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterFilm(QWidget *parent = nullptr);
    ~AjouterFilm();
    Film validation_donnees();

private slots:
    void AjoutPhoto();


private:
    Ui::AjouterFilm *ui;
    Film mFilm;
};

#endif // AJOUTERFILM_H
