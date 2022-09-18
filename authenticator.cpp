#include "authenticator.h"

Authenticator::Authenticator(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
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



    return true;
}

const QString &Authenticator::descr() const
{
    return this->m_descr;
}

void Authenticator::setDescr(const QString &newDescr)
{
    this->m_descr = newDescr;
}

const User* Authenticator::getAuthenticatedUser() const
{
    return this->authenticatedUser;
}
