#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QObject>
#include "user.h"

class Authenticator : public QObject
{
    Q_OBJECT

public:

    explicit Authenticator(QObject *parent = nullptr, const QString &descr = "");
    bool authenticate(QString username, QString password);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

    const User &getAuthenticatedUser() const;
    void setAuthenticatedUser(const User *newAuthenticatedUser);

private:

    QString m_descr;
    User authenticatedUser;

private:


};

#endif // AUTHENTICATOR_H
