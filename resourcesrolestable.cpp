#include "resourcesrolestable.h"

ResourcesRolesTable::ResourcesRolesTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

bool ResourcesRolesTable::findByResourceId(QSqlQuery &query, quint32 resourceId)
{
    QString cmd = "SELECT can_create, can_delete, can_execute, can_read, can_update, created, is_owner, modified, resource_id, role_id FROM resources_roles WHERE resource_id = :resource_id;";
    query.prepare(cmd);
    query.bindValue(":resource_id", resourceId);

    bool ok = this->exec(query);

    return ok;
}

bool ResourcesRolesTable::findByRoleId(QSqlQuery &query, quint32 roleId)
{
    QString cmd = "SELECT can_create, can_delete, can_execute, can_read, can_update, created, is_owner, modified, resource_id, role_id FROM resources_roles WHERE role_id = :role_id;";
    query.prepare(cmd);
    query.bindValue(":role_id", roleId);

    bool ok = this->exec(query);

    return ok;
}

const QString &ResourcesRolesTable::descr() const
{
    return this->m_descr;
}

void ResourcesRolesTable::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool ResourcesRolesTable::exec(QSqlQuery &query)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen())
    {
        return false;
    }

    //qInfo() << "SQL: " << query.executedQuery();
    bool ok =  query.exec();

    if (!ok)
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }

    return ok;
}
