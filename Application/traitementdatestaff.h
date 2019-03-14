#ifndef TRAITEMENTDATESTAFF_H
#define TRAITEMENTDATESTAFF_H
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
#include <QSqlQuery>

QSqlTableModel* CreateModelStaff (QObject *ui);

QSortFilterProxyModel* CreateSortingModelStaff (QObject *ui,QSqlTableModel *StaffModel);

void AjoutStaff(Staff staffAdd,QSqlTableModel *StaffModel );

void DeleteStaff(QSortFilterProxyModel *StaffSortingModel,QModelIndex IndexASuppr,QSqlTableModel *StaffModel);

void modificationstaff(Staff staffAdd,QSqlTableModel *StaffModel,QSortFilterProxyModel *StaffSortingModel,QModelIndex IndexAModifier);

QPixmap photobytearraytoPixmapStaff(QSortFilterProxyModel *FilmSortingModel, QModelIndex indexselected);
#endif // TRAITEMENTDATESTAFF_H
