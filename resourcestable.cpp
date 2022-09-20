#include "resourcestable.h"

ResourcesTable::ResourcesTable(QObject *parent)
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

QSqlRelationalTableModel *ResourcesTable::getModel() const
{
    return this->model;
}

void ResourcesTable::initializeModel()
{
    this->model->setTable("resources");
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->model->setHeaderData(1, Qt::Horizontal, QObject::tr("Path"));
    this->model->setHeaderData(2, Qt::Horizontal, QObject::tr("Type"));
    this->model->select();
}
