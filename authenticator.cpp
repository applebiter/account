#include "authenticator.h"

Authenticator::Authenticator(QObject *parent)
    : QObject{parent}
{
    this->isAuthenticated = false;
}

bool Authenticator::authenticate(QString username, QString password)
{
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpen = db.isOpen();

    if (!isOpen)
    {
        this->errors.insert(QString("Database error:"), QString("Unable to open a connection to the database."));
        return false;
    }

    User *user = new User();

    if (!user->loadByUsername(username))
    {
        this->errors.insert(QString("Authentication error:"), QString("Unable to find the specified user in the database."));
        return false;
    }

    QCryptographicHash *hash = new QCryptographicHash(QCryptographicHash::Sha512);
    hash->addData(user->getUuid().toUtf8());
    hash->addData(password.toUtf8());
    QString encodedPassword = hash->result().toBase64();

    QSqlQuery query;
    QString cmd = "SELECT created, email, id, is_activated, modified, password, role_id, secret, username, uuid FROM users WHERE username LIKE :username AND password LIKE :password AND is_activated = 1;";
    query.prepare(cmd);
    query.bindValue(":username", username);
    query.bindValue(":password", encodedPassword);

    if (query.exec())
    {
        if (query.first())
        {
            QSqlRecord record = query.record();
            this->authenticatedUser->setCreated(QString(record.value(0).toString()));
            this->authenticatedUser->setEmail(QString(record.value(1).toString()));
            this->authenticatedUser->setId(record.value(2).toInt());
            this->authenticatedUser->setIsActivated(record.value(3).toBool());
            this->authenticatedUser->setModified(QString(record.value(4).toString()));
            this->authenticatedUser->setPassword(QString(record.value(5).toString()));
            this->authenticatedUser->setRoleId(record.value(6).toInt());
            this->authenticatedUser->setSecret(QString(record.value(7).toString()));
            this->authenticatedUser->setUsername(QString(record.value(8).toString()));
            this->authenticatedUser->setUuid(QString(record.value(9).toString()));
            this->isAuthenticated = true;
            emit this->userLoggedIn();
        }
    }

    return this->isAuthenticated;
}

void Authenticator::clearAuthenticatedUser()
{
    this->authenticatedUser = new User(this);
    this->isAuthenticated = false;
    emit this->userLoggedOut();
}

void Authenticator::clearErrors()
{
    this->errors.clear();
}

User *Authenticator::getAuthenticatedUser() const
{
    return this->authenticatedUser;
}

bool Authenticator::getIsAuthenticated() const
{
    return this->isAuthenticated;
}

const QHash<QString, QString> &Authenticator::getErrors() const
{
    return this->errors;
}

bool Authenticator::hasErrors()
{
    if (this->errors.isEmpty())
    {
        return false;
    }

    return true;
}
