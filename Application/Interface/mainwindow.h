#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <qsortfilterproxymodel.h>
#include "ajouterfilm.h"
#include<QDataWidgetMapper>
#include<QFileDialog>
#include<QComboBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void VerouillageFilm();
    void VerouillageStaff();
    void initialisation();
    void ModelFilmSetup();
    void ModelStaffSetup();
    void DeverouillageFilm();
    void DeverouillageStaff();
    int conversion_en_int();
    void DisplayFilm(Film f);
    QDataWidgetMapper * MappingFilm(QSortFilterProxyModel *FilmSortingModel);
    QDataWidgetMapper * MappingStaff(QSortFilterProxyModel *StaffSortingModel);


private slots:
    void ajouter_Film();

    void enregistrementAjoutFilm(Film filmAjoute);
    void conversion_min_en_heure();
    void apparition_texte();
    void suppressionFilm();
    void modificationFilm();
   // void annuler();
    void modif_pris_en_compte_Film();
    void masquer_texte_Film();
    void filtreRechercheFilm(QString tri);
    void filtreRechercheStaff(QString tri);
    void demasquage_btn();
    void cache_btn();

    void image_loading(QModelIndex);

    void annuler_la_modif_Film();
    void modification_photo_Film();
    void liaisonFilmReal();



private:
    Ui::MainWindow *ui;
    QSqlTableModel *mFilmModel;
    QSortFilterProxyModel *mFilmSortingModel;
    QSqlTableModel *mStaffModel;
    QSortFilterProxyModel *mStaffSortingModel;

};

#endif // MAINWINDOW_H

