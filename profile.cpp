#include "profile.h"

Profile::Profile(QObject *parent)
    : QObject{parent}
{
    this->create();
}

void Profile::hydrate(QHash<QString, QVariant> &data)
{
    if (data.contains("avatar"))
    {
        this->avatar = data["avatar"].toString();
    }
    if (data.contains("fullName"))
    {
        this->fullName = data["fullName"].toString();
    }
    if (data.contains("id"))
    {
        this->id = data["id"].toInt();
    }
    if (data.contains("longBiography"))
    {
        this->longBiography = data["longBiography"].toString();
    }
    if (data.contains("shortBiography"))
    {
        this->shortBiography = data["shortBiography"].toString();
    }
    if (data.contains("userId"))
    {
        this->userId = data["userId"].toInt();
    }
}

void Profile::begin()
{
    QSqlDatabase::database().transaction();
}

void Profile::commit()
{
    QSqlDatabase::database().commit();
}

void Profile::rollback()
{
    QSqlDatabase::database().rollback();
}

bool Profile::open()
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

void Profile::create()
{
    this->avatar = "";
    this->fullName = "";
    this->id = 0;
    this->longBiography = "";
    this->shortBiography = "";
    this->userId = 0;
}

bool Profile::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT avatar, full_name, id, long_biography, short_biography, user_id FROM profiles where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);
    bool ret = false;

    if (this->exec(query))
    {
        if (query.first())
        {
            QSqlRecord record = query.record();
            this->avatar = record.value(0).toString();
            this->fullName = record.value(1).toString();
            this->id = record.value(2).toInt();
            this->longBiography = record.value(3).toString();
            this->shortBiography = record.value(4).toString();
            this->userId = record.value(5).toInt();
            ret = true;
        }
    }

    return ret;
}

bool Profile::save()
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

void Profile::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM profiles where id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);
    this->exec(query);
}

const QString &Profile::getAvatar() const
{
    return this->avatar;
}

void Profile::setAvatar(const QString &newAvatar)
{
    if (this->avatar == newAvatar)
    {
        return;
    }

    this->avatar = newAvatar.toUtf8();
    emit this->avatarChanged();
}

const QString &Profile::getFullName() const
{
    return this->fullName;
}

void Profile::setFullName(const QString &newFullName)
{
    if (this->fullName == newFullName)
    {
        return;
    }

    this->fullName = newFullName.toUtf8();
    emit this->fullNameChanged();
}

quint32 Profile::getId() const
{
    return this->id;
}

void Profile::setId(quint32 newId)
{
    if (this->id == newId)
    {
        return;
    }

    this->id = newId;
    emit this->idChanged();
}

const QString &Profile::getLongBiography() const
{
    return this->longBiography;
}

void Profile::setLongBiography(const QString &newLongBiography)
{
    if (this->longBiography == newLongBiography)
    {
        return;
    }

    this->longBiography = newLongBiography.toUtf8();
    emit this->longBiographyChanged();
}

const QString &Profile::getShortBiography() const
{
    return this->shortBiography;
}

void Profile::setShortBiography(const QString &newShortBiography)
{
    if (this->shortBiography == newShortBiography)
    {
        return;
    }

    this->shortBiography = newShortBiography.toUtf8();
    emit this->shortBiographyChanged();
}

quint32 Profile::getUserId() const
{
    return this->userId;
}

const QHash<QString, QString> &Profile::getErrors() const
{
    return this->errors;
}

bool Profile::hasErrors()
{
    if (this->errors.isEmpty())
    {
        return false;
    }

    return true;
}

void Profile::setUserId(quint32 newUserId)
{
    if (this->userId == newUserId)
    {
        return;
    }

    this->userId = newUserId;
    emit this->userIdChanged();
}

void Profile::clearErrors()
{
    this->errors.clear();
}

bool Profile::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO profiles (avatar, full_name, long_biography, short_biography, user_id) VALUES (:avatar, :full_name, :long_biography, :short_biography, :user_id);";
    query.prepare(cmd);
    query.bindValue(":avatar", this->avatar);
    query.bindValue(":full_name", this->fullName);
    query.bindValue(":long_biography", this->longBiography);
    query.bindValue(":short_biography", this->shortBiography);
    query.bindValue(":user_id", this->userId);
    bool ret = false;

    if (this->exec(query))
    {
        this->id = query.lastInsertId().toInt();
        ret = true;
    }

    return ret;
}

bool Profile::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE profiles SET avatar = :avatar, full_name = :full_name, long_biography = :long_biography, short_biography = :short_biography, user_id = :user_id WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":avatar", this->avatar);
    query.bindValue(":full_name", this->fullName);
    query.bindValue(":long_biography", this->longBiography);
    query.bindValue(":short_biography", this->shortBiography);
    query.bindValue(":user_id", this->userId);
    query.bindValue(":id", this->id);
    return this->exec(query);
}

bool Profile::exec(QSqlQuery &query)
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
