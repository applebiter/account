#include "devicestable.h"

DevicesTable::DevicesTable(QObject *parent)
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

QSqlRelationalTableModel *DevicesTable::getModel() const
{
    return this->model;
}

void DevicesTable::initializeModel()
{
    this->model->setTable("devices");
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->setRelation(1, QSqlRelation("users", "id", "username"));
    this->model->setRelation(3, QSqlRelation("carriers", "id", "name"));
    this->model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->model->setHeaderData(1, Qt::Horizontal, QObject::tr("User"));
    this->model->setHeaderData(2, Qt::Horizontal, QObject::tr("Name"));
    this->model->setHeaderData(3, Qt::Horizontal, QObject::tr("Carrier"));
    this->model->setHeaderData(4, Qt::Horizontal, QObject::tr("Number"));
    this->model->setHeaderData(5, Qt::Horizontal, QObject::tr("Created"));
    this->model->setHeaderData(6, Qt::Horizontal, QObject::tr("Modified"));
    this->model->select();
}
