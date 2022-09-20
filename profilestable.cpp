#include "profilestable.h"

ProfilesTable::ProfilesTable(QObject *parent)
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

QSqlRelationalTableModel *ProfilesTable::getModel() const
{
    return this->model;
}

void ProfilesTable::initializeModel()
{
    this->model->setTable("profiles");
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->setRelation(1, QSqlRelation("users", "id", "username"));
    this->model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->model->setHeaderData(1, Qt::Horizontal, QObject::tr("User"));
    this->model->setHeaderData(2, Qt::Horizontal, QObject::tr("Avatar"));
    this->model->setHeaderData(3, Qt::Horizontal, QObject::tr("Full Name"));
    this->model->removeColumn(4);
    this->model->removeColumn(5);
    this->model->select();
}
