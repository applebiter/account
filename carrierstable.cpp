#include "carrierstable.h"

// temp hack to make the error messages go away until I've filled in stubs

CarriersTable::CarriersTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

bool CarriersTable::findByCountryId(QSqlQuery &query, quint32 countryId)
{
    QString cmd = "SELECT country_id, gateway, id, name FROM carriers where country_id = :country_id;";
    query.prepare(cmd);
    query.bindValue(":country_id", countryId);

    bool ok = this->exec(query);

    return ok;
}

bool CarriersTable::findByName(QSqlQuery &query, QString name)
{
    QString cmd = "SELECT country_id, gateway, id, name FROM carriers where name = :name;";
    query.prepare(cmd);
    query.bindValue(":name", name);

    bool ok = this->exec(query);

    return ok;
}

const QString &CarriersTable::descr() const
{
    return m_descr;
}

void CarriersTable::setDescr(const QString &newDescr)
{
    m_descr = newDescr;
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
