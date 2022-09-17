#include "devicestable.h"

DevicesTable::DevicesTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

bool DevicesTable::findByUserId(quint32 userId)
{
    QSqlQuery query;
    QString cmd = "SELECT carrier_id, created, id, modified, name, number, user_id FROM devices where user_id = :user_id;";
    query.prepare(cmd);
    query.bindValue(":user_id", userId);

    bool ok = this->exec(query);

    return ok;
}

const QString &DevicesTable::descr() const
{
    return m_descr;
}

void DevicesTable::setDescr(const QString &newDescr)
{
    m_descr = newDescr;
}

bool DevicesTable::exec(QSqlQuery &query)
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
