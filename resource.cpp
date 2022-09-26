#include "resource.h"

Resource::Resource(QObject *parent)
    : QObject{parent}
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
    bool conn = db.isOpen();

    if (!conn)
    {
        this->errors.insert(QString("Database error:"), QString("Unable to open a connection to the database."));
        emit this->errorOccurred();
    }

    return conn;
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
    bool ret = false;

    if (this->exec(query))
    {
        if (query.first())
        {
            QSqlRecord record = query.record();
            this->id = record.value(0).toInt();
            this->path = record.value(1).toString();
            this->type = record.value(2).toString();
            ret = true;
        }
    }

    return ret;
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
    {
        return;
    }

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
    {
        return;
    }

    this->path = newPath.toUtf8();
    emit this->pathChanged();
}

const QString &Resource::getType() const
{
    return this->type;
}

const QHash<QString, QString> &Resource::getErrors() const
{
    return this->errors;
}

bool Resource::hasErrors()
{
    if (this->errors.isEmpty())
    {
        return false;
    }

    return true;
}

void Resource::setType(const QString &newType)
{
    if (this->type == newType)
       {
         return;
    }

    this->type = newType.toUtf8();
    emit this->typeChanged();
}

void Resource::clearErrors()
{
    this->errors.clear();
}

bool Resource::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO resources (path, type) VALUES (:path, :type);";
    query.prepare(cmd);
    query.bindValue(":path", this->path);
    query.bindValue(":type", this->type);
    bool ret = false;

    if (this->exec(query))
    {
        this->id = query.lastInsertId().toInt();
        ret = true;
    }

    return ret;
}

bool Resource::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE resources SET path = :path, type = :type WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":path", this->path);
    query.bindValue(":type", this->type);
    query.bindValue(":id", this->id);
    return this->exec(query);
}

bool Resource::exec(QSqlQuery &query)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen())
    {
        this->errors.insert(QString("Database error:"), QString("Unable to open a connection to the database."));
        emit this->errorOccurred();
        return false;
    }

    //qInfo() << "SQL: " << query.executedQuery();
    bool ok =  query.exec();

    if (!ok)
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
        this->errors.insert(QString("Database error:"), QString("An error occurred while executing the query."));
        this->errors.insert(QString("DB last error:"), db.lastError().text());
        this->errors.insert(QString("Query last error:"), query.lastError().text());
        emit this->errorOccurred();
    }

    return ok;
}
