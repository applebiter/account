#include "role.h"

Role::Role(QObject *parent)
    : QObject{parent}
{
    this->create();
}

void Role::hydrate(QHash<QString, QVariant> &data)
{
    if (data.contains("id"))
    {
        this->id = data["id"].toInt();
    }
    if (data.contains("name"))
    {
        this->name = data["name"].toString();
    }
}

void Role::begin()
{
    QSqlDatabase::database().transaction();
}

void Role::commit()
{
    QSqlDatabase::database().commit();
}

void Role::rollback()
{
    QSqlDatabase::database().rollback();
}

bool Role::open()
{
    QSqlDatabase db = QSqlDatabase::database();
    return db.isOpen();
}

void Role::create()
{
    this->id = 0;
    this->name = "";
}

bool Role::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT id, name FROM roles where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);
    bool ret = false;

    if (this->exec(query))
    {
        if (query.first())
        {
            QSqlRecord record = query.record();
            this->id = record.value(0).toInt();
            this->name = record.value(1).toString();
            ret = true;
        }
    }

    return ret;
}

bool Role::loadByName(QString value)
{
    QSqlQuery query;
    QString cmd = "SELECT id, name FROM roles where name = :name;";
    query.prepare(cmd);
    query.bindValue(":name", value);
    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->id = record.value(0).toInt();
            this->name = record.value(1).toString();
        }
    }

    return ok;
}

bool Role::save()
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

void Role::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM roles WHERE id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);
    this->exec(query);
}

quint32 Role::getId() const
{
    return this->id;
}

void Role::setId(quint32 newId)
{
    if (this->id == newId)
    {
        return;
    }

    this->id = newId;
    emit this->idChanged();
}

const QString &Role::getName() const
{
    return this->name;
}

void Role::setName(const QString &newName)
{
    if (this->name == newName)
    {
        return;
    }

    this->name = newName.toUtf8();
    emit this->nameChanged();
}

bool Role::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO roles (id, name) VALUES (:id, :name);";
    query.prepare(cmd);
    query.bindValue(":id", this->id);
    query.bindValue(":name", this->name);
    bool ret = false;

    if (this->exec(query))
    {
        this->id = query.lastInsertId().toInt();
        ret = true;
    }

    return ret;
}

bool Role::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE roles SET name = :name WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":name", this->name);
    query.bindValue(":id", this->id);
    return this->exec(query);
}

bool Role::exec(QSqlQuery &query)
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
