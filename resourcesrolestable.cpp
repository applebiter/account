#include "resourcesrolestable.h"

ResourcesRolesTable::ResourcesRolesTable(QObject *parent)
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

QSqlRelationalTableModel *ResourcesRolesTable::getModel() const
{
    return this->model;
}

void ResourcesRolesTable::initializeModel()
{
    this->model->setTable("resources_roles");
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->setRelation(1, QSqlRelation("resources", "id", "path"));
    this->model->setRelation(2, QSqlRelation("roles", "id", "name"));
    this->model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->model->setHeaderData(1, Qt::Horizontal, QObject::tr("Resource"));
    this->model->setHeaderData(2, Qt::Horizontal, QObject::tr("Role"));
    this->model->setHeaderData(3, Qt::Horizontal, QObject::tr("Can Create"));
    this->model->setHeaderData(4, Qt::Horizontal, QObject::tr("Can Read"));
    this->model->setHeaderData(5, Qt::Horizontal, QObject::tr("Can Update"));
    this->model->setHeaderData(6, Qt::Horizontal, QObject::tr("Can Delete"));
    this->model->setHeaderData(7, Qt::Horizontal, QObject::tr("Can Execute"));
    this->model->setHeaderData(8, Qt::Horizontal, QObject::tr("Is Owner"));
    this->model->setHeaderData(9, Qt::Horizontal, QObject::tr("Created"));
    this->model->setHeaderData(10, Qt::Horizontal, QObject::tr("Modified"));
    this->model->select();
}
