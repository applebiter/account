#include "statestable.h"

StatesTable::StatesTable(QObject *parent)
    : QObject{parent}
{

}

quint32 StatesTable::count(QSqlQuery &query)
{
    quint32 count = 0;
    QString cmd = "SELECT COUNT(*) as count FROM states;";
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

bool StatesTable::findByCountryId(QSqlQuery &query, quint32 countryId)
{
    QString cmd = "SELECT code, country_id, id, name FROM states WHERE country_id = :country_id;";
    query.prepare(cmd);
    query.bindValue(":country_id", countryId);

    bool ok = this->exec(query);

    return ok;
}

const QString &StatesTable::descr() const
{
    return this->m_descr;
}

void StatesTable::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool StatesTable::exec(QSqlQuery &query)
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
