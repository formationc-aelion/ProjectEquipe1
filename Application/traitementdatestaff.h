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

QSqlTableModel* CreateModelStaff (QObject *ui)
{
QSqlDatabase db = QSqlDatabase::database("connexionBDDfilm");
QSqlTableModel *mStaffModel = new QSqlTableModel (ui,db);
mStaffModel->setTable("staff");
mStaffModel->select();
mStaffModel->setEditStrategy(QSqlTableModel::OnManualSubmit);

return mStaffModel;
}

QSortFilterProxyModel* CreateSortingModelStaff (QObject *ui,QSqlTableModel *StaffModel)
{
QSqlDatabase db = QSqlDatabase::database("connexionBDDfilm");
QSortFilterProxyModel *mStaffSortingModel = new QSortFilterProxyModel(ui);
mStaffSortingModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
mStaffSortingModel->setSortCaseSensitivity(Qt::CaseInsensitive);
mStaffSortingModel->sort(1, Qt::AscendingOrder);
mStaffSortingModel->setDynamicSortFilter(true);
mStaffSortingModel->setSourceModel(StaffModel);
return mStaffSortingModel;
}

#endif // TRAITEMENTDATESTAFF_H
