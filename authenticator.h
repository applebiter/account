#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <QObject>
#include <sodium.h>
#include "user.h"

class Authenticator : public QObject
{
    Q_OBJECT

public:

    explicit Authenticator(QObject *parent = nullptr);

    User *getAuthenticatedUser() const;
    bool getIsAuthenticated() const;
    const QHash<QString, QString> &getErrors() const;
    bool hasErrors();

public slots:

    bool authenticate(QString username, QString password);
    void clearAuthenticatedUser();
    void clearErrors();

signals:

    void userLoggedIn();
    void userLoggedOut();

private:

    User *authenticatedUser = new User(this);
    bool isAuthenticated;
    QHash<QString, QString> errors;
};

#endif // AUTHENTICATOR_H
