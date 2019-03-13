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


#endif // TRAITEMENTDATESTAFF_H
