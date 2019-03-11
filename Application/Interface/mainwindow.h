#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <qsortfilterproxymodel.h>
#include "ajouterfilm.h"
#include<QDataWidgetMapper>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Verouillage();
    void Deverouillage();
    int conversion_en_int();

private slots:
    void ajouter_Film();
    void conversion_min_en_heure();
    void apparition_texte();
    void suppression();
    void modification();
   // void annuler();
    void modif_pris_en_compte();

private:
    Ui::MainWindow *ui;
    QSqlTableModel *mFilmModel;
    QSortFilterProxyModel *mFilmFilteredModel;
};

#endif // MAINWINDOW_H

