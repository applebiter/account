#include "countriestable.h"

CountriesTable::CountriesTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

quint32 CountriesTable::count(QSqlQuery &query)
{
    quint32 count = 0;
    QString cmd = "SELECT COUNT(*) as count FROM countries;";
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

bool CountriesTable::findByCode(QSqlQuery &query, QString code)
{
    QString cmd = "SELECT code, id, name FROM countries where code = :code;";
    query.prepare(cmd);
    query.bindValue(":code", code);

    bool ok = this->exec(query);

    return ok;
}

bool CountriesTable::findByName(QSqlQuery &query, QString name)
{
    QString cmd = "SELECT code, id, name FROM countries where name = :name;";
    query.prepare(cmd);
    query.bindValue(":name", name);

    bool ok = this->exec(query);

    return ok;
}

const QString &CountriesTable::descr() const
{
    return m_descr;
}

void CountriesTable::setDescr(const QString &newDescr)
{
    m_descr = newDescr;
}

bool CountriesTable::exec(QSqlQuery &query)
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
