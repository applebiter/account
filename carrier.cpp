#include "carrier.h"

Carrier::Carrier(QObject *parent)
    : QObject{parent}
{
    this->create();
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
    bool isOpen = db.isOpen();

    return isOpen;
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
    QString cmd = "SELECT country_id, gateway, id, name FROM account.carriers where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->countryId = record.value(0).toInt();
            this->gateway = record.value(1).toString();
            this->id = record.value(2).toInt();
            this->name = record.value(3).toString();
        }
    }

    return ok;
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
    QString cmd = "DELETE FROM account.carriers where id = :id";
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
        return;
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
        return;
    this->gateway = newGateway;
    emit this->gatewayChanged();
}

quint32 Carrier::getId() const
{
    return this->id;
}

void Carrier::setId(quint32 newId)
{
    if (this->id == newId)
        return;
    this->id = newId;
    emit this->idChanged();
}

const QString &Carrier::getName() const
{
    return this->name;
}

void Carrier::setName(const QString &newName)
{
    if (this->name == newName)
        return;
    this->name = newName;
    emit this->nameChanged();
}

bool Carrier::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO account.carriers (country_id, gateway, name) VALUES (:country_id, :gateway, :name);";
    query.prepare(cmd);
    query.bindValue(":country_id", this->countryId);
    query.bindValue(":gateway", this->gateway);
    query.bindValue(":name", this->name);

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

bool Carrier::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE account.carriers SET country_id = :country_id, gateway = :gateway, name = :name WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":country_id", this->countryId);
    query.bindValue(":gateway", this->gateway);
    query.bindValue(":name", this->name);
    query.bindValue(":id", this->id);

    bool ok = exec(query);

    return ok;
}

bool Carrier::exec(QSqlQuery &query)
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