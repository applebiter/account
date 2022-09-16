#include "carrierstable.h"

// temp hack to make the error messages go away until I've filled in stubs

CarriersTable::CarriersTable(QObject *parent)
    : QObject{parent}
{
    this->model = new QSqlTableModel(this);
    model->setTable("carriers");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();
}

void CarriersTable::findByCountryId(quint32 countryId)
{

}

void CarriersTable::findByName(QString name)
{

}
