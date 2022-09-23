#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "account_global.h"
#include "../simple-mail/src/SimpleMail"
#include <QCryptographicHash>
#include <QFile>
#include <QObject>
#include "authenticator.h"
#include "user.h"

class ACCOUNT_EXPORT Account : public QObject
{
    Q_OBJECT

public:

    explicit Account(QObject *parent = nullptr);

    User* getAthenticatedUser() const;
    Authenticator *getAuthenticator() const;
    const QHash<QString, QString> &getErrors() const;
    bool hasErrors();

public slots:

    bool activateAccount(QString username, QString secret);
    bool changePassword(QString currentPassword, QString newPassword);
    void clearErrors();
    bool login(QString username, QString password);
    void logout();
    bool registerAccount(QString username, QString email, QString password);
    bool resetPassword1(QString username);
    bool resetPassword2(QString username, QString secret);

private:

    Authenticator *authenticator;
    User *authenticatedUser;
    QHash<QString, QString> errors;
    bool isLoggedIn;

private:

    QString getRandomString();
};
#endif // ACCOUNT_H
