#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <qsortfilterproxymodel.h>
#include "ajouterfilm.h"
#include<QDataWidgetMapper>
#include<QFileDialog>
#include <Staff.h>

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
    void DisplayStaff(Staff staffAjoute);
    Staff validation_donneesStaff();
    QDataWidgetMapper * MappingFilm(QSortFilterProxyModel *FilmSortingModel);
    QDataWidgetMapper * MappingStaff(QSortFilterProxyModel *StaffSortingModel);

    Staff staff() const;

private slots:
    void ajouter_Film();
    void ajouter_Staff();
    void enregistrementAjoutFilm(Film filmAjoute);
    void enregistrementAjoutStaff(Staff staffAjoute);
    void conversion_min_en_heure();
    void apparition_texte();
    void suppressionFilm();
    void suppressionStaff();
    void modificationFilm();
    void modificationStaff();
   // void annuler();
    void modif_pris_en_compte_Film();
    void modif_pris_en_compte_Staff();
    void masquer_texte_Film();
    void filtreRechercheFilm(QString tri);
    void filtreRechercheStaff(QString tri);
    void demasquage_btn();
    void demasquage_btnStaff();
    void cache_btn();
    void cache_btnStaff();

    void image_loading(QModelIndex);

    void annuler_la_modif_Film();
    void annuler_la_modif_Staff();
    void modification_photo_Film();
    void modification_photo_Staff();



private:
    Ui::MainWindow *ui;
    QSqlTableModel *mFilmModel;
    QSortFilterProxyModel *mFilmSortingModel;
    QSqlTableModel *mStaffModel;
    QSortFilterProxyModel *mStaffSortingModel;
    Staff mStaff;

};

#endif // MAINWINDOW_H

