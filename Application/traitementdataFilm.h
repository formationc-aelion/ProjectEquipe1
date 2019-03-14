#ifndef TRAITEMENTDATA_H
#define TRAITEMENTDATA_H
#include <QObject>
#include"film.h"
#include "Staff.h"
#include<QDebug>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>



QSqlTableModel* CreateModelFilm (QObject *ui);

QSortFilterProxyModel* CreateSortingModelFilm (QObject *ui,QSqlTableModel *FilmModel);

int Conversionint(QString DureeFilm);

void AjoutFilm(Film FilmAdd,QSqlTableModel *FilmModel );

QString ConversionMinHeure(int DureeMin);

void DeleteFilm(QSortFilterProxyModel *FilmSortingModel,QModelIndex IndexASuppr,QSqlTableModel *FilmModel);

void modificationfilm(Film FilmAdd,QSqlTableModel *FilmModel,QSortFilterProxyModel *FilmSortingModel,QModelIndex IndexAModifier);

QPixmap photobytearraytoPixmap(QSortFilterProxyModel *FilmSortingModel, QModelIndex indexselected);
QByteArray photoPixMaptoBytearray( const QPixmap *image);
#endif // TRAITEMENTDATA_H
