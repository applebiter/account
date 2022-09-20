#include "userstable.h"

UsersTable::UsersTable(QObject *parent)
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

QSqlRelationalTableModel *UsersTable::getModel() const
{
    return this->model;
}

void UsersTable::initializeModel()
{
    this->model->setTable("users");
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->setRelation(6, QSqlRelation("roles", "id", "name"));
    this->model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->model->removeColumn(1);
    this->model->removeColumn(2);
    this->model->setHeaderData(3, Qt::Horizontal, QObject::tr("Username"));
    this->model->removeColumn(4);
    this->model->removeColumn(5);
    this->model->setHeaderData(6, Qt::Horizontal, QObject::tr("Role"));
    this->model->setHeaderData(7, Qt::Horizontal, QObject::tr("Is Activated"));
    this->model->setHeaderData(8, Qt::Horizontal, QObject::tr("Created"));
    this->model->setHeaderData(9, Qt::Horizontal, QObject::tr("modified"));
    this->model->select();
}
