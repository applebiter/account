#include "carrierstable.h"

CarriersTable::CarriersTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

quint32 CarriersTable::count(QSqlQuery &query)
{
    quint32 count = 0;
    QString cmd = "SELECT COUNT(*) as count FROM carriers;";
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

bool CarriersTable::findByCountryId(QSqlQuery &query, quint32 countryId)
{
    QString cmd = "SELECT country_id, gateway, id, name FROM carriers WHERE country_id = :country_id;";
    query.prepare(cmd);
    query.bindValue(":country_id", countryId);

    bool ok = this->exec(query);

    return ok;
}

bool CarriersTable::findByName(QSqlQuery &query, QString name)
{
    QString cmd = "SELECT country_id, gateway, id, name FROM carriers WHERE name = :name;";
    query.prepare(cmd);
    query.bindValue(":name", name);

    bool ok = this->exec(query);

    return ok;
}

const QString &CarriersTable::descr() const
{
    return this->m_descr;
}

void CarriersTable::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool CarriersTable::exec(QSqlQuery &query)
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
