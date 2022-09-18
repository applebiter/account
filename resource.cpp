#include "resource.h"

Resource::Resource(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{
    this->create();
}

void Resource::hydrate(QHash<QString, QVariant> &data)
{
    if (data.contains("id"))
    {
        this->id = data["id"].toInt();
    }
    if (data.contains("path"))
    {
        this->path = data["path"].toString();
    }
    if (data.contains("type"))
    {
        this->type = data["type"].toString();
    }
}

void Resource::begin()
{
    QSqlDatabase::database().transaction();
}

void Resource::commit()
{
   QSqlDatabase::database().commit();
}

void Resource::rollback()
{
    QSqlDatabase::database().rollback();
}

bool Resource::open()
{
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpen = db.isOpen();

    return isOpen;
}

void Resource::create()
{
    this->id = 0;
    this->path = "";
    this->type = "";
}

bool Resource::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT id, path, type FROM resources where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->id = record.value(0).toInt();
            this->path = record.value(1).toString();
            this->type = record.value(2).toString();
        }
    }

    return ok;
}

bool Resource::save()
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

void Resource::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM resources where id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);

    this->exec(query);
}

quint32 Resource::getId() const
{
    return this->id;
}

void Resource::setId(quint32 newId)
{
    if (this->id == newId)
        return;
    this->id = newId;
    emit this->idChanged();
}

const QString &Resource::getPath() const
{
    return this->path;
}

void Resource::setPath(const QString &newPath)
{
    if (this->path == newPath)
        return;
    this->path = newPath.toUtf8();
    emit this->pathChanged();
}

const QString &Resource::getType() const
{
    return this->type;
}

void Resource::setType(const QString &newType)
{
    if (this->type == newType)
        return;
    this->type = newType.toUtf8();
    emit this->typeChanged();
}

const QString &Resource::descr() const
{
    return this->m_descr;
}

void Resource::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool Resource::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO resources (path, type) VALUES (:path, :type);";
    query.prepare(cmd);
    query.bindValue(":path", this->path);
    query.bindValue(":type", this->type);

    bool ok = exec(query);

    if (ok)
    {
        this->id = query.lastInsertId().toInt();
    }
    else
    {
        this->id = 0;
    }

    return ok;
}

bool Resource::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE resources SET path = :path, type = :type WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":path", this->path);
    query.bindValue(":type", this->type);
    query.bindValue(":id", this->id);

    bool ok = exec(query);

    return ok;
}

bool Resource::exec(QSqlQuery &query)
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
