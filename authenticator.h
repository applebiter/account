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

    User *getAuthenticatedUser() const;
    bool getIsAuthenticated() const;
    const QHash<QString, QString> &getErrors() const;
    bool hasErrors();

signals:

    void userLoggedIn();
    void userLoggedOut();

public slots:

    bool authenticate(QString username, QString password);
    void clearAuthenticatedUser();
    void clearErrors();

private:

    User *authenticatedUser = new User(this);
    bool isAuthenticated;
    QHash<QString, QString> errors;
};

#endif // AUTHENTICATOR_H
