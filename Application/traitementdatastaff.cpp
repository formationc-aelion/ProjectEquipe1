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

void AjoutStaff(Staff staffAdd,QSqlTableModel *StaffModel )
{
    StaffModel->insertRow(StaffModel->rowCount());
    int lastrow=StaffModel->rowCount()-1;

    StaffModel->setData(StaffModel->index(lastrow,1),staffAdd.nom());
    StaffModel->setData(StaffModel->index(lastrow,2),staffAdd.dateNaissance());
    StaffModel->setData(StaffModel->index(lastrow,3),staffAdd.nationaliteA());
    StaffModel->setData(StaffModel->index(lastrow,4),staffAdd.nationaliteB());
    StaffModel->setData(StaffModel->index(lastrow,5),staffAdd.professionA());
    StaffModel->setData(StaffModel->index(lastrow,6),staffAdd.professionB());
    StaffModel->setData(StaffModel->index(lastrow,7),staffAdd.professionC());
    StaffModel->setData(StaffModel->index(lastrow,8),staffAdd.photo());
    StaffModel->setData(StaffModel->index(lastrow,9),staffAdd.bio());

    StaffModel->submitAll();
}

void DeleteStaff(QSortFilterProxyModel *StaffSortingModel,QModelIndex IndexASuppr,QSqlTableModel *StaffModel)
{
    StaffSortingModel->removeRow(IndexASuppr.row());

    StaffModel->submitAll();
    StaffModel->select();
}

void modificationStaff(Staff staffAdd,QSqlTableModel *StaffModel,QSortFilterProxyModel *StaffSortingModel,QModelIndex IndexAModifier)
{

    StaffSortingModel->setData(StaffSortingModel->index(IndexAModifier.row(),1),staffAdd.nom());
    StaffSortingModel->setData(StaffSortingModel->index(IndexAModifier.row(),2),staffAdd.dateNaissance());
    StaffSortingModel->setData(StaffSortingModel->index(IndexAModifier.row(),3),staffAdd.nationaliteA());
    StaffSortingModel->setData(StaffSortingModel->index(IndexAModifier.row(),4),staffAdd.nationaliteB());
    StaffSortingModel->setData(StaffSortingModel->index(IndexAModifier.row(),5),staffAdd.professionA());
    StaffSortingModel->setData(StaffSortingModel->index(IndexAModifier.row(),6),staffAdd.professionB());
    StaffSortingModel->setData(StaffSortingModel->index(IndexAModifier.row(),7),staffAdd.professionC());
    StaffSortingModel->setData(StaffSortingModel->index(IndexAModifier.row(),7),staffAdd.photo());
    StaffSortingModel->setData(StaffSortingModel->index(IndexAModifier.row(),7),staffAdd.bio());
    StaffModel->submitAll();

}

