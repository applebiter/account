#include "preferencestable.h"

PreferencesTable::PreferencesTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

bool PreferencesTable::findByUserId(QSqlQuery &query, quint32 userId)
{
    QString cmd = "SELECT id, theme, user_id FROM preferences WHERE user_id = :user_id;";
    query.prepare(cmd);
    query.bindValue(":user_id", userId);

    bool ok = this->exec(query);

    return ok;
}

const QString &PreferencesTable::descr() const
{
    return this->m_descr;
}

void PreferencesTable::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool PreferencesTable::exec(QSqlQuery &query)
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
