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
    bool isOpen = db.isOpen();

    return isOpen;
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

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->code = record.value(0).toString();
            this->id = record.value(1).toInt();
            this->name = record.value(2).toString();
        }
    }

    return ok;
}

bool Country::loadByCode(QString value)
{
    QSqlQuery query;
    QString cmd = "SELECT code, id, name FROM countries where code = :code;";
    query.prepare(cmd);
    query.bindValue(":code", value);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->code = record.value(0).toString();
            this->id = record.value(1).toInt();
            this->name = record.value(2).toString();
        }
    }

    return ok;
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
        return;
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
        return;
    this->id = newId;
    emit this->idChanged();
}

const QString &Country::getName() const
{
    return this->name;
}

void Country::setName(const QString &newName)
{
    if (this->name == newName)
        return;
    this->name = newName.toUtf8();
    emit this->nameChanged();
}

bool Country::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO countries (code, name) VALUES (:code, :name);";
    query.prepare(cmd);
    query.bindValue(":code", this->code);
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

bool Country::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE countries SET code = :code, name = :name WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":code", this->code);
    query.bindValue(":name", this->name);
    query.bindValue(":id", this->id);

    bool ok = exec(query);

    return ok;
}

bool Country::exec(QSqlQuery &query)
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
