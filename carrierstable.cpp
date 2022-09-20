#include "carrierstable.h"

CarriersTable::CarriersTable(QObject *parent)
    : QObject{parent}
{
    this->db = QSqlDatabase::database();
    bool ok = db.open();
    if (!ok)
    {
        qInfo() << "Failed to open connection!";
        qInfo() << db.lastError().text();
    }
    this->model = new QSqlRelationalTableModel(this, this->db);
    this->initializeModel();
}

QSqlRelationalTableModel *CarriersTable::getModel() const
{
    return this->model;
}

void CarriersTable::initializeModel()
{
    this->model->setTable("carriers");
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->setRelation(1, QSqlRelation("countries", "id", "name"));
    this->model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->model->setHeaderData(1, Qt::Horizontal, QObject::tr("Country"));
    this->model->setHeaderData(2, Qt::Horizontal, QObject::tr("Name"));
    this->model->setHeaderData(3, Qt::Horizontal, QObject::tr("Gateway"));
    this->model->select();
}
