#include "rolestable.h"

RolesTable::RolesTable(QObject *parent)
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

QSqlRelationalTableModel *RolesTable::getModel() const
{
    return this->model;
}

void RolesTable::initializeModel()
{
    this->model->setTable("roles");
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->model->setHeaderData(2, Qt::Horizontal, QObject::tr("Name"));
    this->model->select();
}
