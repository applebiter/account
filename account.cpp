#include "account.h"

Account::Account(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}

bool Account::activateAccount(quint32 userId, QString secret)
{
    return true;
}

bool Account::changePassword(QString currentPassword, QString newPassword)
{
    return true;
}

bool Account::login(QString username, QString password)
{
    return true;
}

bool Account::logout()
{
    return true;
}

bool Account::registerAccount(QString username, QString email, QString password)
{
    return true;
}

bool Account::resetPassword(QString username)
{
    return true;
}

quint32 Account::createAccount(QHash<QString, QVariant> data)
{
    return 1;
}

bool Account::updateAccount(quint32 userId, QHash<QString, QVariant> data)
{
    return true;
}

bool Account::removeAccount(quint32 userId)
{
    return true;
}

const QString &Account::descr() const
{
    return this->m_descr;
}

void Account::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

const User &Account::getUser() const
{
    return this->user;
}

const Preference &Account::getPreference() const
{
    return this->preference;
}

const Profile &Account::getProfile() const
{
    return this->profile;
}
