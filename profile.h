#ifndef PROFILE_H
#define PROFILE_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class Profile : public QObject
{
    Q_OBJECT

public:

    explicit Profile(QObject *parent = nullptr);
    void begin();
    void commit();
    void rollback();
    bool open();
    void create();
    bool load(quint32 ident);
    bool save();
    void remove();

    const QString &getAvatar() const;
    void setAvatar(const QString &newAvatar);

    const QString &getFullName() const;
    void setFullName(const QString &newFullName);

    quint32 getId() const;
    void setId(quint32 newId);

    const QString &getLongBiography() const;
    void setLongBiography(const QString &newLongBiography);

    const QString &getShortBiography() const;
    void setShortBiography(const QString &newShortBiography);

    quint32 getUserId() const;
    void setUserId(quint32 newUserId);

signals:

    void avatarChanged();

    void fullNameChanged();

    void idChanged();

    void longBiographyChanged();

    void shortBiographyChanged();

    void userIdChanged();

public slots:

private:

    QString avatar;
    QString fullName;
    quint32 id;
    QString longBiography;
    QString shortBiography;
    quint32 userId;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);
    Q_PROPERTY(QString avatar READ getAvatar WRITE setAvatar NOTIFY avatarChanged)
    Q_PROPERTY(QString fullName READ getFullName WRITE setFullName NOTIFY fullNameChanged)
    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString longBiography READ getLongBiography WRITE setLongBiography NOTIFY longBiographyChanged)
    Q_PROPERTY(QString shortBiography READ getShortBiography WRITE setShortBiography NOTIFY shortBiographyChanged)
    Q_PROPERTY(quint32 userId READ getUserId WRITE setUserId NOTIFY userIdChanged)
};

#endif // PROFILE_H
