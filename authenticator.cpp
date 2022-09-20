#include "authenticator.h"

Authenticator::Authenticator(QObject *parent)
    : QObject{parent}, isAuthenticated((false))
{

}

bool Authenticator::authenticate(QString username, QString password)
{
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpen = db.isOpen();

    if (!isOpen)
    {
        return false;
    }

    QCryptographicHash *hash = new QCryptographicHash(QCryptographicHash::Sha256);
    hash->addData(password.toUtf8());
    QString encodedPassword = hash->result().toBase64();

    QSqlQuery query;
    QString cmd = "SELECT created, email, id, is_activated, modified, password, role_id, secret, username, uuid FROM users WHERE username = :username AND password = :password AND is_active = 1;";
    query.prepare(cmd);
    query.bindValue(":username", username);
    query.bindValue(":password", encodedPassword);

    if (query.exec())
    {
        query.first();

        QSqlRecord record = query.record();
        QHash<QString, QVariant> data;
        data["created"] = record.value(0);
        data["email"] = record.value(1);
        data["id"] = record.value(2);
        data["isActivated"] = record.value(3);
        data["modified"] = record.value(4);
        data["password"] = record.value(5);
        data["roleId"] = record.value(6);
        data["secret"] = record.value(7);
        data["username"] = record.value(8);
        data["uuid"] = record.value(9);

        this->authenticatedUser->hydrate(data);
        this->isAuthenticated = true;
        emit this->userLoggedIn();
    }

    return this->isAuthenticated;
}

void Authenticator::clearAuthenticatedUser()
{
    this->authenticatedUser = new User(this);
    this->isAuthenticated = false;
    emit this->userLoggedOut();
}

const User *Authenticator::getAuthenticatedUser() const
{
    return this->authenticatedUser;
}

bool Authenticator::getIsAuthenticated() const
{
    return this->isAuthenticated;
}
