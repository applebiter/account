#include "countriestable.h"

CountriesTable::CountriesTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

void CountriesTable::findByCode(QString code)
{
    QSqlQuery query;
    QString cmd = "SELECT code, id, name FROM countries where code = :code;";
    query.prepare(cmd);
    query.bindValue(":code", code);

    bool ok = this->exec(query);

    if (ok)
    {

    }
}

void CountriesTable::findByName(QString name)
{
    QSqlQuery query;
    QString cmd = "SELECT code, id, name FROM countries where name = :name;";
    query.prepare(cmd);
    query.bindValue(":name", name);

    bool ok = this->exec(query);

    if (ok)
    {

    }
}
