#include <traitementdatestaff.h>

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
