#include "resourcestable.h"

ResourcesTable::ResourcesTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

quint32 ResourcesTable::count(QSqlQuery &query)
{
    quint32 count = 0;
    QString cmd = "SELECT COUNT(*) as count FROM resources;";
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

bool ResourcesTable::findByPath(QSqlQuery &query, QString path)
{
    QString cmd = "SELECT id, path, type FROM resources WHERE path = :path;";
    query.prepare(cmd);
    query.bindValue(":path", path);

    bool ok = this->exec(query);

    return ok;
}

bool ResourcesTable::findByType(QSqlQuery &query, QString type)
{
    QString cmd = "SELECT id, path, type FROM resources WHERE type = :type;";
    query.prepare(cmd);
    query.bindValue(":type", type);

    bool ok = this->exec(query);

    return ok;
}

const QString &ResourcesTable::descr() const
{
    return this->m_descr;
}

void ResourcesTable::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool ResourcesTable::exec(QSqlQuery &query)
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
