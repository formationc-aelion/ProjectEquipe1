#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <qsortfilterproxymodel.h>
#include "ajouterfilm.h"
#include<QDataWidgetMapper>
#include<QFileDialog>

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
    void DisplayFilm(Film f);

private slots:
    void ajouter_Film();
    void enregistrementAjout();
    void conversion_min_en_heure();
    void apparition_texte();
    void suppression();
    void modification();
   // void annuler();
    void modif_pris_en_compte();
    void masquer_texte();
    void filtreRecherche(QString tri);
    void demasquage_btn();
    void cache_btn();
    void annuler_la_modif();
    void modification_photo();


private:
    Ui::MainWindow *ui;
    QSqlTableModel *mFilmModel;
    QSortFilterProxyModel *mFilmSortingModel;

};

#endif // MAINWINDOW_H

