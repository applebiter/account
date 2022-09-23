#ifndef USER_H
#define USER_H

#include <QCryptographicHash>
#include <QDebug>
#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QUuid>
#include <QVariant>

class User : public QObject
{
    Q_OBJECT

public:

    explicit User(QObject *parent = nullptr);

    void begin();
    void commit();
    void rollback();
    bool open();
    void create();

    const QString &getCreated() const;
    const QString &getEmail() const;
    quint32 getId() const;
    bool getIsActivated() const;
    const QString &getModified() const;
    const QString &getPassword() const;
    quint32 getRoleId() const;
    const QString &getSecret() const;
    const QString &getUsername() const;
    const QString &getUuid() const;

public slots:

    void hydrate(QHash<QString, QVariant> &data);
    bool load(quint32 ident);
    bool loadActivate(QString username, QString secret);
    bool loadByEmail(QString value);
    bool loadByUsername(QString value);
    bool loadByUuid(QString value);
    bool save();
    void remove();

    void setCreated(const QString &newCreated);
    void setEmail(const QString &newEmail);
    void setId(quint32 newId);
    void setIsActivated(bool newIsActivated);
    void setModified(const QString &newModified);
    void setPassword(const QString &newPassword);
    void setRoleId(quint32 newRoleId);
    void setSecret(const QString &newSecret);
    void setUsername(const QString &newUsername);
    void setUuid(const QString &newUuid);

signals:

    void createdChanged();
    void emailChanged();
    void idChanged();
    void isActivatedChanged();
    void modifiedChanged();
    void passwordChanged();
    void roleIdChanged();
    void secretChanged();
    void usernameChanged();
    void uuidChanged();

private:

    QString created;
    QString email;
    quint32 id;
    bool isActivated;
    QString modified;
    QString password;
    quint32 roleId;
    QString secret;
    QString username;
    QString uuid;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(QString created READ getCreated WRITE setCreated NOTIFY createdChanged)
    Q_PROPERTY(QString email READ getEmail WRITE setEmail NOTIFY emailChanged)
    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(bool isActivated READ getIsActivated WRITE setIsActivated NOTIFY isActivatedChanged)
    Q_PROPERTY(QString modified READ getModified WRITE setModified NOTIFY modifiedChanged)
    Q_PROPERTY(QString password READ getPassword WRITE setPassword NOTIFY passwordChanged)
    Q_PROPERTY(quint32 roleId READ getRoleId WRITE setRoleId NOTIFY roleIdChanged)
    Q_PROPERTY(QString secret READ getSecret WRITE setSecret NOTIFY secretChanged)
    Q_PROPERTY(QString username READ getUsername WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString uuid READ getUuid WRITE setUuid NOTIFY uuidChanged)
};

#endif // USER_H
