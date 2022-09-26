#include "country.h"

Country::Country(QObject *parent)
    : QObject{parent}
{
    this->create();
}

void Country::hydrate(QHash<QString, QVariant> &data)
{
    if (data.contains("code"))
    {
        this->code = data["code"].toString();
    }
    if (data.contains("id"))
    {
        this->id = data["id"].toInt();
    }
    if (data.contains("name"))
    {
        this->name = data["name"].toString();
    }
}

void Country::begin()
{
    QSqlDatabase::database().transaction();
}

void Country::commit()
{
   QSqlDatabase::database().commit();
}

void Country::rollback()
{
    QSqlDatabase::database().rollback();
}

bool Country::open()
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

void Country::create()
{
    this->code = "";
    this->id = 0;
    this->name = "";
}

bool Country::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT code, id, name FROM countries where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);
    bool ret = false;

    if (this->exec(query))
    {
        if (query.first())
        {
            QSqlRecord record = query.record();
            this->code = record.value(0).toString();
            this->id = record.value(1).toInt();
            this->name = record.value(2).toString();
            ret = true;
        }
    }

    return ret;
}

bool Country::loadByCode(QString value)
{
    QSqlQuery query;
    QString cmd = "SELECT code, id, name FROM countries where code = :code;";
    query.prepare(cmd);
    query.bindValue(":code", value);
    bool ret = false;

    if (this->exec(query))
    {
        if (query.first())
        {
            QSqlRecord record = query.record();
            this->code = record.value(0).toString();
            this->id = record.value(1).toInt();
            this->name = record.value(2).toString();
            ret = true;
        }
    }

    return ret;
}

bool Country::save()
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

void Country::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM countries where id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);
    this->exec(query);
}

const QString &Country::getCode() const
{
    return this->code;
}

void Country::setCode(const QString &newCode)
{
    if (this->code == newCode)
    {
        return;
    }

    this->code = newCode.toUtf8();
    emit this->codeChanged();
}

quint32 Country::getId() const
{
    return this->id;
}

void Country::setId(quint32 newId)
{
    if (this->id == newId)
    {
        return;
    }

    this->id = newId;
    emit this->idChanged();
}

const QString &Country::getName() const
{
    return this->name;
}

const QHash<QString, QString> &Country::getErrors() const
{
    return this->errors;
}

bool Country::hasErrors()
{
    if (this->errors.isEmpty())
    {
        return false;
    }

    return true;
}

void Country::setName(const QString &newName)
{
    if (this->name == newName)
    {
        return;
    }

    this->name = newName.toUtf8();
    emit this->nameChanged();
}

void Country::clearErrors()
{
    this->errors.clear();
}

bool Country::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO countries (code, name) VALUES (:code, :name);";
    query.prepare(cmd);
    query.bindValue(":code", this->code);
    query.bindValue(":name", this->name);
    bool ret = false;

    if (this->exec(query))
    {
        this->id = query.lastInsertId().toInt();
        ret = true;
    }

    return ret;
}

bool Country::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE countries SET code = :code, name = :name WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":code", this->code);
    query.bindValue(":name", this->name);
    query.bindValue(":id", this->id);
    return this->exec(query);
}

bool Country::exec(QSqlQuery &query)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen())
    {
        this->errors.insert(QString("Database error:"), QString("Unable to open a connection to the database."));
        emit this->errorOccurred();
        return false;
    }

    //qInfo() << "Exec: " << query.executedQuery();
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
