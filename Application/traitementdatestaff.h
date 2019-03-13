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

QSqlTableModel* CreateModelStaff (QObject *ui);

QSortFilterProxyModel* CreateSortingModelStaff (QObject *ui,QSqlTableModel *StaffModel);

void AjoutStaff(Staff staffAdd,QSqlTableModel *StaffModel );
void DeleteStaff(QSortFilterProxyModel *StaffSortingModel,QModelIndex IndexASuppr,QSqlTableModel *StaffModel);

void modificationStaff(Film staffAdd,QSqlTableModel *StaffModel,QSortFilterProxyModel *StaffSortingModel,QModelIndex IndexAModifier);


#endif // TRAITEMENTDATESTAFF_H
