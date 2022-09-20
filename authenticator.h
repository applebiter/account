#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QCryptographicHash>
#include <QObject>
#include "user.h"

class Authenticator : public QObject
{
    Q_OBJECT

public:

    explicit Authenticator(QObject *parent = nullptr);

    const User *getAuthenticatedUser() const;
    bool getIsAuthenticated() const;

signals:

    void userLoggedIn();
    void userLoggedOut();

public slots:

    bool authenticate(QString username, QString password);
    void clearAuthenticatedUser();

private:

    User *authenticatedUser;
    bool isAuthenticated;
};

#endif // AUTHENTICATOR_H
