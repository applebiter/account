#include "user.h"

User::User(QObject *parent)
    : QObject{parent}
{
    this->create();
}

void User::begin()
{
    QSqlDatabase::database().transaction();
}

void User::commit()
{
    QSqlDatabase::database().commit();
}

void User::rollback()
{
    QSqlDatabase::database().rollback();
}

bool User::open()
{
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpen = db.isOpen();

    return isOpen;
}

void User::create()
{
    this->created = "";
    this->email = "";
    this->id = 0;
    this->isActivated = false;
    this->modified = "";
    this->password = "";
    this->roleId = 0;
    this->secret = "";
    this->username = "";
    this->uuid = "";
}

bool User::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT created, email, id, is_activated, modified, password, role_id, secret, username, uuid FROM account.users where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->created = record.value(0).toString();
            this->email = record.value(1).toString();
            this->id = record.value(2).toInt();
            this->isActivated = record.value(3).toBool();
            this->modified = record.value(4).toString();
            this->password = record.value(5).toString();
            this->roleId = record.value(6).toInt();
            this->secret = record.value(7).toString();
            this->username = record.value(8).toString();
            this->uuid = record.value(9).toString();
        }
    }

    return ok;
}

bool User::save()
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

void User::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM account.users WHERE id = :id";
    query.prepare(cmd);
    query.bindValue(":id", this->id);

    this->exec(query);
}

const QString &User::getCreated() const
{
    return this->created;
}

void User::setCreated(const QString &newCreated)
{
    if (this->created == newCreated)
        return;
    this->created = newCreated;
    emit this->createdChanged();
}

const QString &User::getEmail() const
{
    return this->email;
}

void User::setEmail(const QString &newEmail)
{
    if (this->email == newEmail)
        return;
    this->email = newEmail;
    emit this->emailChanged();
}

quint32 User::getId() const
{
    return this->id;
}

void User::setId(quint32 newId)
{
    if (this->id == newId)
        return;
    this->id = newId;
    emit this->idChanged();
}

bool User::getIsActivated() const
{
    return this->isActivated;
}

void User::setIsActivated(bool newIsActivated)
{
    if (this->isActivated == newIsActivated)
        return;
    this->isActivated = newIsActivated;
    emit this->isActivatedChanged();
}

const QString &User::getModified() const
{
    return this->modified;
}

void User::setModified(const QString &newModified)
{
    if (this->modified == newModified)
        return;
    this->modified = newModified;
    emit this->modifiedChanged();
}

const QString &User::getPassword() const
{
    return this->password;
}

void User::setPassword(const QString &newPassword)
{
    if (this->password == newPassword)
        return;
    this->password = newPassword;
    emit this->passwordChanged();
}

quint32 User::getRoleId() const
{
    return this->roleId;
}

void User::setRoleId(quint32 newRoleId)
{
    if (this->roleId == newRoleId)
        return;
    this->roleId = newRoleId;
    emit this->roleIdChanged();
}

const QString &User::getSecret() const
{
    return this->secret;
}

void User::setSecret(const QString &newSecret)
{
    if (this->secret == newSecret)
        return;
    this->secret = newSecret;
    emit this->secretChanged();
}

const QString &User::getUsername() const
{
    return this->username;
}

void User::setUsername(const QString &newUsername)
{
    if (this->username == newUsername)
        return;
    this->username = newUsername;
    emit this->usernameChanged();
}

const QString &User::getUuid() const
{
    return this->uuid;
}

void User::setUuid(const QString &newUuid)
{
    if (this->uuid == newUuid)
        return;
    this->uuid = newUuid;
    emit this->uuidChanged();
}

bool User::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO account.users (created, email, is_activated, modified, password, role_id, secret, username, password) VALUES (:created, :email, :is_activated, :modified, :password, :role_id, :secret, :username, :password);";
    query.prepare(cmd);
    query.bindValue(":created", this->created);
    query.bindValue(":email", this->email);
    query.bindValue(":is_activated", this->isActivated);
    query.bindValue(":modified", this->modified);
    query.bindValue(":password", this->password);
    query.bindValue(":role_id", this->roleId);
    query.bindValue(":secret", this->secret);
    query.bindValue(":username", this->username);
    query.bindValue(":uuid", this->uuid);

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

bool User::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE account.users SET created = :created, email = :email, is_activated = :is_activated, modified = :modified, password = :password, role_id = :role_id, secret = :secret, username = :username, uuid = :uuid WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":created", this->created);
    query.bindValue(":email", this->email);
    query.bindValue(":is_activated", this->isActivated);
    query.bindValue(":modified", this->modified);
    query.bindValue(":password", this->password);
    query.bindValue(":role_id", this->roleId);
    query.bindValue(":secret", this->secret);
    query.bindValue(":username", this->username);
    query.bindValue(":uuid", this->uuid);

    bool ok = exec(query);

    return ok;
}

bool User::exec(QSqlQuery &query)
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
