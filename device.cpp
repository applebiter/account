#include "device.h"

Device::Device(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{
    this->create();
}

void Device::hydrate(QHash<QString, QVariant> &data)
{
    if (data.contains("carrierId"))
    {
        this->carrierId = data["carrierId"].toInt();
    }
    if (data.contains("created"))
    {
        this->created = data["created"].toString();
    }
    if (data.contains("id"))
    {
        this->id = data["id"].toInt();
    }
    if (data.contains("modified"))
    {
        this->modified = data["modified"].toString();
    }
    if (data.contains("name"))
    {
        this->name = data["name"].toString();
    }
    if (data.contains("created"))
    {
        this->number = data["number"].toString();
    }
    if (data.contains("userId"))
    {
        this->userId = data["userId"].toInt();
    }
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
    this->created = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss");
    this->id = 0;
    this->modified = this->created;
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
    this->created = newCreated.toUtf8();
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
    this->modified = newModified.toUtf8();
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
    this->name = newName.toUtf8();
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
    this->number = newNumber.toUtf8();
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

const QString &Device::descr() const
{
    return this->m_descr;
}

void Device::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool Device::insert()
{
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
    this->modified = QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss");
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
