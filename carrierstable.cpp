#include "carrierstable.h"

// temp hack to make the error messages go away until I've filled in stubs

CarriersTable::CarriersTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

void CarriersTable::findByCountryId(quint32 countryId)
{
    QSqlQuery query;
    QString cmd = "SELECT country_id, gateway, id, name FROM carriers where country_id = :country_id;";
    query.prepare(cmd);
    query.bindValue(":country_id", countryId);

    bool ok = this->exec(query);

    if (ok)
    {

    }
}

void CarriersTable::findByName(QString name)
{
    QSqlQuery query;
    QString cmd = "SELECT country_id, gateway, id, name FROM carriers where name = :name;";
    query.prepare(cmd);
    query.bindValue(":name", name);

    bool ok = this->exec(query);

    if (ok)
    {

    }
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
