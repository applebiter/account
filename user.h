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

    explicit User(QObject *parent = nullptr, const QString &descr = "");
    void hydrate(QHash<QString, QVariant> data);
    void begin();
    void commit();
    void rollback();
    bool open();
    void create();
    bool load(quint32 ident);
    bool loadByEmail(QString value);
    bool loadByUsername(QString value);
    bool loadByUuid(QString value);
    bool save();
    void remove();

    const QString &getCreated() const;
    void setCreated(const QString &newCreated);

    const QString &getEmail() const;
    void setEmail(const QString &newEmail);

    quint32 getId() const;
    void setId(quint32 newId);

    bool getIsActivated() const;
    void setIsActivated(bool newIsActivated);

    const QString &getModified() const;
    void setModified(const QString &newModified);

    const QString &getPassword() const;
    void setPassword(const QString &newPassword);

    quint32 getRoleId() const;
    void setRoleId(quint32 newRoleId);

    const QString &getSecret() const;
    void setSecret(const QString &newSecret);

    const QString &getUsername() const;
    void setUsername(const QString &newUsername);

    const QString &getUuid() const;
    void setUuid(const QString &newUuid);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

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

public slots:

private:

    QString m_descr;
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
