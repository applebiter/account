#include "state.h"

State::State(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{
    this->create();
}

void State::hydrate(QHash<QString, QVariant> data)
{
    if (data.contains("code"))
    {
        this->code = data["code"].toString();
    }
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

void State::begin()
{
    QSqlDatabase::database().transaction();
}

void State::commit()
{
    QSqlDatabase::database().commit();
}

void State::rollback()
{
   QSqlDatabase::database().rollback();
}

bool State::open()
{
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpen = db.isOpen();

    return isOpen;
}

void State::create()
{
    this->code = "";
    this->countryId = 0;
    this->id = 0;
    this->name = "";
}

bool State::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT code, country_id, id, name FROM states where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->code = record.value(0).toString();
            this->countryId = record.value(1).toInt();
            this->id = record.value(2).toInt();
            this->name = record.value(3).toString();
        }
    }

    return ok;
}

bool State::loadByCode(QString value)
{
    QSqlQuery query;
    QString cmd = "SELECT code, country_id, id, name FROM states where code = :code;";
    query.prepare(cmd);
    query.bindValue(":code", value);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->code = record.value(0).toString();
            this->countryId = record.value(1).toInt();
            this->id = record.value(2).toInt();
            this->name = record.value(3).toString();
        }
    }

    return ok;
}

bool State::loadByName(QString value)
{
    QSqlQuery query;
    QString cmd = "SELECT code, country_id, id, name FROM states where name = :name;";
    query.prepare(cmd);
    query.bindValue(":name", value);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->code = record.value(0).toString();
            this->countryId = record.value(1).toInt();
            this->id = record.value(2).toInt();
            this->name = record.value(3).toString();
        }
    }

    return ok;
}

bool State::save()
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

void State::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM states WHERE id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);

    this->exec(query);
}

const QString &State::getCode() const
{
    return this->code;
}

void State::setCode(const QString &newCode)
{
    if (this->code == newCode)
        return;
    this->code = newCode.toUtf8();
    emit this->codeChanged();
}

quint32 State::getCountryId() const
{
    return this->countryId;
}

void State::setCountryId(quint32 newCountryId)
{
    if (this->countryId == newCountryId)
        return;
    this->countryId = newCountryId;
    emit this->countryIdChanged();
}

quint32 State::getId() const
{
    return this->id;
}

void State::setId(quint32 newId)
{
    if (this->id == newId)
        return;
    this->id = newId;
    emit this->idChanged();
}

const QString &State::getName() const
{
    return this->name;
}

void State::setName(const QString &newName)
{
    if (this->name == newName.toUtf8())
        return;
    this->name = newName;
    emit this->nameChanged();
}

const QString &State::descr() const
{
    return this->m_descr;
}

void State::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

bool State::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO states (code, country_id, name) VALUES (:code, :country_id, :name);";
    query.prepare(cmd);
    query.bindValue(":code", this->code);
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

bool State::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE states SET code = :code, country_id = :country_id, name = :name WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":code", this->code);
    query.bindValue(":country_id", this->countryId);
    query.bindValue(":name", this->name);
    query.bindValue(":id", this->id);

    bool ok = exec(query);

    return ok;
}

bool State::exec(QSqlQuery &query)
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
