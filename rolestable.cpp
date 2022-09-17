#include "rolestable.h"

RolesTable::RolesTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

quint32 RolesTable::count(QSqlQuery &query)
{
    quint32 count = 0;
    QString cmd = "SELECT COUNT(*) as count FROM roles;";
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

const QString &RolesTable::descr() const
{
    return this->m_descr;
}

void RolesTable::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool RolesTable::exec(QSqlQuery &query)
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
