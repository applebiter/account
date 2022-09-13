#include "device.h"

Device::Device(QObject *parent)
    : QObject{parent}
{
    this->create();
}

void Device::begin()
{
    QSqlDatabase::database().transaction();
}

void Device::commit()
{
    QSqlDatabase::database().commit();
}

void Device::rollback()
{
   QSqlDatabase::database().rollback();
}

bool Device::open()
{
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpen = db.isOpen();

    return isOpen;
}

void Device::create()
{
    this->carrierId = 0;
    this->created = "";
    this->id = 0;
    this->modified = "";
    this->name = "";
    this->number = "";
    this->userId = 0;
}

bool Device::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT carrier_id, created, id, modified, name, number, user_id FROM account.devices where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->carrierId = record.value(0).toInt();
            this->created = record.value(1).toString();
            this->id = record.value(2).toInt();
            this->modified = record.value(3).toString();
            this->name = record.value(4).toString();
            this->number = record.value(5).toString();
            this->userId = record.value(6).toInt();
        }
    }

    return ok;
}

bool Device::save()
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

void Device::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM account.devices where id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);

    this->exec(query);
}

quint32 Device::getCarrierId() const
{
    return this->carrierId;
}

void Device::setCarrierId(quint32 newCarrierId)
{
    if (this->carrierId == newCarrierId)
        return;
    this->carrierId = newCarrierId;
    emit this->carrierIdChanged();
}

const QString &Device::getCreated() const
{
    return this->created;
}

void Device::setCreated(const QString &newCreated)
{
    if (this->created == newCreated)
        return;
    this->created = newCreated;
    emit this->createdChanged();
}

quint32 Device::getId() const
{
    return this->id;
}

void Device::setId(quint32 newId)
{
    if (this->id == newId)
        return;
    this->id = newId;
    emit this->idChanged();
}

const QString &Device::getModified() const
{
    return this->modified;
}

void Device::setModified(const QString &newModified)
{
    if (this->modified == newModified)
        return;
    this->modified = newModified;
    emit this->modifiedChanged();
}

const QString &Device::getName() const
{
    return this->name;
}

void Device::setName(const QString &newName)
{
    if (this->name == newName)
        return;
    this->name = newName;
    emit this->nameChanged();
}

const QString &Device::getNumber() const
{
    return this->number;
}

void Device::setNumber(const QString &newNumber)
{
    if (this->number == newNumber)
        return;
    this->number = newNumber;
    emit this->numberChanged();
}

quint32 Device::getUserId() const
{
    return this->userId;
}

void Device::setUserId(quint32 newUserId)
{
    if (this->userId == newUserId)
        return;
    this->userId = newUserId;
    emit this->userIdChanged();
}

bool Device::insert()
{
    this->carrierId = 0;
    this->created = "";
    this->id = 0;
    this->modified = "";
    this->name = "";
    this->number = "";
    this->userId = 0;

    QSqlQuery query;
    QString cmd = "INSERT INTO account.devices (carrier_id, created, modified, name, number, user_id) VALUES (:carrier_id, :created, :modified, :name, :number, :user_id);";
    query.prepare(cmd);
    query.bindValue(":carrier_id", this->carrierId);
    query.bindValue(":created", this->created);
    query.bindValue(":modified", this->modified);
    query.bindValue(":name", this->name);
    query.bindValue(":number", this->number);
    query.bindValue(":user_id", this->userId);

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

bool Device::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE account.devices SET carrier_id = :carrier_id, created = :created, modified = :modified, name = :name, number = :number, user_id = :user_id WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":carrier_id", this->carrierId);
    query.bindValue(":created", this->created);
    query.bindValue(":modified", this->modified);
    query.bindValue(":name", this->name);
    query.bindValue(":number", this->number);
    query.bindValue(":user_id", this->userId);
    query.bindValue(":id", this->id);

    bool ok = exec(query);

    return ok;
}

bool Device::exec(QSqlQuery &query)
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
