#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "account_global.h"
#include <QObject>
#include "preference.h"
#include "profile.h"
#include "user.h"

class ACCOUNT_EXPORT Account : public QObject
{
    Q_OBJECT

public:

    explicit Account(QObject *parent = nullptr, const QString &descr = "");
    bool activateAccount(quint32 userId, QString secret);
    bool changePassword(QString currentPassword, QString newPassword);
    bool login(QString username, QString password);
    bool logout();
    bool registerAccount(QString username, QString email, QString password);
    bool resetPassword(QString username);
    quint32 createAccount(QHash<QString, QVariant> data);
    bool updateAccount(quint32 userId, QHash<QString, QVariant> data);
    bool removeAccount(quint32 userId);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

    const User* getUser() const;
    void setUser(const User* newUser);

    const Preference* getPreference() const;
    void setPreference(const Preference* newPreference);

    const Profile* getProfile() const;
    void setProfile(const Profile* newProfile);

private:

    QString m_descr;
    User* user;
    Preference* preference;
    Profile* profile;
};
#endif // ACCOUNT_H
