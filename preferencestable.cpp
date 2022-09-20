#include "preferencestable.h"

PreferencesTable::PreferencesTable(QObject *parent)
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

QSqlRelationalTableModel *PreferencesTable::getModel() const
{
    return this->model;
}

void PreferencesTable::initializeModel()
{
    this->model->setTable("preferences");
    this->model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    this->model->setRelation(1, QSqlRelation("users", "id", "username"));
    this->model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    this->model->setHeaderData(1, Qt::Horizontal, QObject::tr("User"));
    this->model->setHeaderData(2, Qt::Horizontal, QObject::tr("Theme"));
    this->model->select();
}
