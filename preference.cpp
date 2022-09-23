#include "preference.h"

Preference::Preference(QObject *parent)
    : QObject{parent}
{
    this->create();
}

void Preference::hydrate(QHash<QString, QVariant> &data)
{
    if (data.contains("id"))
    {
        this->id = data["id"].toInt();
    }
    if (data.contains("theme"))
        {
            this->theme = data["theme"].toString();
        }
    if (data.contains("userId"))
    {
        this->userId = data["userId"].toInt();
    }
}

void Preference::begin()
{
    QSqlDatabase::database().transaction();
}

void Preference::commit()
{
    QSqlDatabase::database().commit();
}

void Preference::rollback()
{
    QSqlDatabase::database().rollback();
}

bool Preference::open()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.isOpen();
}

void Preference::create()
{
    this->id = 0;
    this->theme = "";
    this->userId = 0;
}

bool Preference::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT id, theme, user_id FROM preferences where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);
    bool ret = false;

    if (this->exec(query))
    {
        if (query.first())
        {
            QSqlRecord record = query.record();
            this->id = record.value(0).toInt();
            this->theme = record.value(1).toString();
            this->userId = record.value(2).toInt();
        }
    }

    return ret;
}

bool Preference::save()
{
    if (this->id > 0)
    {
        return this->update();
    }
    else
    {
        return this->insert();
    }
}

void Preference::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM preferences where id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);
    this->exec(query);
}

quint32 Preference::getId() const
{
    return this->id;
}

void Preference::setId(quint32 newId)
{
    if (this->id == newId)
    {
        return;
    }

    this->id = newId;
    emit this->idChanged();
}

const QString &Preference::getTheme() const
{
    return this->theme;
}

void Preference::setTheme(const QString &newTheme)
{
    if (this->theme == newTheme)
    {
        return;
    }

    this->theme = newTheme.toUtf8();
    emit this->themeChanged();
}

quint32 Preference::getUserId() const
{
    return this->userId;
}

void Preference::setUserId(quint32 newUserId)
{
    if (this->userId == newUserId)
    {
        return;
    }

    this->userId = newUserId;
    emit this->userIdChanged();
}

bool Preference::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO preferences (theme, user_id) VALUES (:theme, :user_id);";
    query.prepare(cmd);
    query.bindValue(":theme", this->theme);
    query.bindValue(":user_id", this->userId);
    bool ret = false;

    if (this->exec(query))
    {
        this->id = query.lastInsertId().toInt();
        ret = true;
    }

    return ret;
}

bool Preference::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE preferences SET theme = :theme, user_id = :user_id WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":theme", this->theme);
    query.bindValue(":user_id", this->userId);
    query.bindValue(":id", this->id);
    return this->exec(query);
}

bool Preference::exec(QSqlQuery &query)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen())
    {
        return false;
    }

    //qInfo() << "Exec: " << query.executedQuery();
    bool ok =  query.exec();

    if (!ok)
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }

    return ok;
}
