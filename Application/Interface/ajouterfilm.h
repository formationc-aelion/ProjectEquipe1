#ifndef AJOUTERFILM_H
#define AJOUTERFILM_H

#include <QDialog>

namespace Ui {
class AjouterFilm;
}

class AjouterFilm : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterFilm(QWidget *parent = nullptr);
    ~AjouterFilm();

private:
    Ui::AjouterFilm *ui;
};

#endif // AJOUTERFILM_H
