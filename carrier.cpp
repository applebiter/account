#include "carrier.h"

Carrier::Carrier(QObject *parent)
    : QObject{parent}
{
    this->create();
}

void Carrier::hydrate(QHash<QString, QVariant> &data)
{
    if (data.contains("countryId"))
    {
        this->countryId = data["countryId"].toInt();
    }
    if (data.contains("gateway"))
    {
        this->gateway = data["gateway"].toString();
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

void Carrier::begin()
{
    QSqlDatabase::database().transaction();
}

void Carrier::commit()
{
    QSqlDatabase::database().commit();
}

void Carrier::rollback()
{
    QSqlDatabase::database().rollback();
}

bool Carrier::open()
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

void Carrier::create()
{
    this->countryId = 0;
    this->gateway = "";
    this->id = 0;
    this->name = "";
}

bool Carrier::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT country_id, gateway, id, name FROM carriers where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);
    bool ret = false;

    if (this->exec(query))
    {
        if (query.first())
        {
            QSqlRecord record = query.record();
            this->countryId = record.value(0).toInt();
            this->gateway = record.value(1).toString();
            this->id = record.value(2).toInt();
            this->name = record.value(3).toString();
            ret = true;
        }
    }

    return ret;
}

bool Carrier::save()
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

void Carrier::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM carriers WHERE id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);
    this->exec(query);
}

quint32 Carrier::getCountryId() const
{
    return this->countryId;
}

void Carrier::setCountryId(quint32 newCountryId)
{
    if (this->countryId == newCountryId)
    {
        return;
    }

    this->countryId = newCountryId;
    emit this->countryIdChanged();
}

const QString &Carrier::getGateway() const
{
    return this->gateway;
}

void Carrier::setGateway(const QString &newGateway)
{
    if (this->gateway == newGateway)
    {
        return;
    }

    this->gateway = newGateway.toUtf8();
    emit this->gatewayChanged();
}

quint32 Carrier::getId() const
{
    return this->id;
}

void Carrier::setId(quint32 newId)
{
    if (this->id == newId)
    {
        return;
    }

    this->id = newId;
    emit this->idChanged();
}

const QString &Carrier::getName() const
{
    return this->name;
}

const QHash<QString, QString> &Carrier::getErrors() const
{
    return this->errors;
}

bool Carrier::hasErrors()
{
    if (this->errors.isEmpty())
    {
        return false;
    }

    return true;
}

void Carrier::setName(const QString &newName)
{
    if (this->name == newName)
    {
        return;
    }

    this->name = newName.toUtf8();
    emit this->nameChanged();
}

void Carrier::clearErrors()
{
    this->errors.clear();
}

bool Carrier::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO carriers (country_id, gateway, name) VALUES (:country_id, :gateway, :name);";
    query.prepare(cmd);
    query.bindValue(":country_id", this->countryId);
    query.bindValue(":gateway", this->gateway);
    query.bindValue(":name", this->name);
    bool ret = false;

    if (this->exec(query))
    {
        this->id = query.lastInsertId().toInt();
        ret = true;
    }

    return ret;
}

bool Carrier::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE carriers SET country_id = :country_id, gateway = :gateway, name = :name WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":country_id", this->countryId);
    query.bindValue(":gateway", this->gateway);
    query.bindValue(":name", this->name);
    query.bindValue(":id", this->id);
    return this->exec(query);
}

bool Carrier::exec(QSqlQuery &query)
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
