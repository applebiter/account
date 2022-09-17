#include "zonestable.h"

ZonesTable::ZonesTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

quint32 ZonesTable::count(QSqlQuery &query)
{
    quint32 count = 0;
    QString cmd = "SELECT COUNT(*) as count FROM zones;";
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

bool ZonesTable::findByCountryId(QSqlQuery &query, quint32 countryId)
{
    QString cmd = "SELECT country_id, id, name FROM zones WHERE country_id = :country_id;";
    query.prepare(cmd);
    query.bindValue(":country_id", countryId);

    bool ok = this->exec(query);

    return ok;
}

const QString &ZonesTable::descr() const
{
    return this->m_descr;
}

void ZonesTable::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool ZonesTable::exec(QSqlQuery &query)
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
