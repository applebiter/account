#include "userstable.h"

UsersTable::UsersTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

quint32 UsersTable::count(QSqlQuery &query)
{
    quint32 count = 0;
    QString cmd = "SELECT COUNT(*) as count FROM users;";
    query.prepare(cmd);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            count = record.value(0).toInt();
        }
    }

    return count;
}

bool UsersTable::findByIsActivated(QSqlQuery &query, bool isActivated)
{
    QString cmd = "SELECT created, email, id, is_activated, modified, password, role_id, secret, username, uuid FROM users WHERE is_activated = :is_activated;";
    query.prepare(cmd);
    query.bindValue(":is_activated", isActivated);

    bool ok = this->exec(query);

    return ok;
}

bool UsersTable::findByRoleId(QSqlQuery &query, quint32 roleId)
{
    QString cmd = "SELECT created, email, id, is_activated, modified, password, role_id, secret, username, uuid FROM users WHERE role_id = :role_id;";
    query.prepare(cmd);
    query.bindValue(":role_id", roleId);

    bool ok = this->exec(query);

    return ok;
}

const QString &UsersTable::descr() const
{
    return this->m_descr;
}

void UsersTable::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool UsersTable::exec(QSqlQuery &query)
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
