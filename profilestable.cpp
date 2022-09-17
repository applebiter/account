#include "profilestable.h"

ProfilesTable::ProfilesTable(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

bool ProfilesTable::findByUserId(QSqlQuery &query, quint32 userId)
{
    QString cmd = "SELECT avatar, full_name, id, long_biography, short_biography, user_id FROM profiles WHERE user_id = :user_id;";
    query.prepare(cmd);
    query.bindValue(":user_id", userId);

    bool ok = this->exec(query);

    return ok;
}

const QString &ProfilesTable::descr() const
{
    return this->m_descr;
}

void ProfilesTable::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool ProfilesTable::exec(QSqlQuery &query)
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
