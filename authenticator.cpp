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
    User *user = new User();

    if (!isOpen)
    {
        this->errors.insert(QString("Database error:"), QString("Unable to open a connection to the database."));
        return false;
    }

    if (!user->loadByUsername(username))
    {
        this->errors.insert(QString("Authentication error:"), QString("Unable to find the specified user in the database."));
        return false;
    }

    if (!user->getIsActivated())
    {
        this->errors.insert(QString("Authentication error:"), QString("The specified user account has not been activated."));
        return false;
    }

    std::string rawPwd = password.toStdString();
    std::string rawHash = user->getPassword().toStdString();

    if (crypto_pwhash_str_verify(rawHash.c_str(), rawPwd.c_str(), strlen(rawPwd.c_str())) != 0)
    {
        this->errors.insert(QString("Authentication error:"), QString("Invalid password."));
        return false;
    }

    this->authenticatedUser = user;
    this->isAuthenticated = true;

    return this->isAuthenticated;
}

void Authenticator::clearAuthenticatedUser()
{
    this->authenticatedUser = nullptr;
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
