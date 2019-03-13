#ifndef TRAITEMENTDATA_H
#define TRAITEMENTDATA_H
#include <QMainWindow>
#include"film.h"
#include "Staff.h"
#include<QDebug>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include <mainwindow.h>


QSqlTableModel* CreateModelFilm (QObject *ui);

QSortFilterProxyModel* CreateSortingModelFilm (QObject *ui,QSqlTableModel *FilmModel);

int Conversionint(QString DureeFilm);

void AjoutFilm(Film FilmAdd,QSqlTableModel *FilmModel );

QString ConversionMinHeure(int DureeMin);

void DeleteFilm(QSortFilterProxyModel *FilmSortingModel,QModelIndex IndexASuppr,QSqlTableModel *FilmModel);

void modificationfilm(Film FilmAdd,QSqlTableModel *FilmModel,QSortFilterProxyModel *FilmSortingModel,QModelIndex IndexAModifier);

#endif // TRAITEMENTDATA_H
