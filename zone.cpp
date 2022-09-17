#include "zone.h"

Zone::Zone(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{
    this->create();
}

void Zone::hydrate(QHash<QString, QVariant> data)
{
    if (data.contains("countryId"))
    {
        this->countryId = data["countryId"].toInt();
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

void Zone::begin()
{
    QSqlDatabase::database().transaction();
}

void Zone::commit()
{
    QSqlDatabase::database().commit();
}

void Zone::rollback()
{
    QSqlDatabase::database().rollback();
}

bool Zone::open()
{
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpen = db.isOpen();

    return isOpen;
}

void Zone::create()
{
    this->countryId = 0;
    this->id = 0;
    this->name = "";
}

bool Zone::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT country_id, id, name FROM zones where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->countryId = record.value(0).toInt();
            this->id = record.value(2).toInt();
            this->name = record.value(3).toString();
        }
    }

    return ok;
}

bool Zone::save()
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

void Zone::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM zones WHERE id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);

    this->exec(query);
}

quint32 Zone::getCountryId() const
{
    return this->countryId;
}

void Zone::setCountryId(quint32 newCountryId)
{
    if (this->countryId == newCountryId)
        return;
    this->countryId = newCountryId;
    emit this->countryIdChanged();
}

quint32 Zone::getId() const
{
    return this->id;
}

void Zone::setId(quint32 newId)
{
    if (this->id == newId)
        return;
    this->id = newId;
    emit this->idChanged();
}

const QString &Zone::getName() const
{
    return this->name;
}

void Zone::setName(const QString &newName)
{
    if (this->name == newName)
        return;
    this->name = newName.toUtf8();
    emit this->nameChanged();
}

const QString &Zone::descr() const
{
    return this->m_descr;
}

void Zone::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool Zone::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO zones (country_id, name) VALUES (:country_id, :name);";
    query.prepare(cmd);
    query.bindValue(":country_id", this->countryId);
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

bool Zone::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE zones SET country_id = :country_id, name = :name WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":country_id", this->countryId);
    query.bindValue(":name", this->name);
    query.bindValue(":id", this->id);

    bool ok = exec(query);

    return ok;
}

bool Zone::exec(QSqlQuery &query)
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
