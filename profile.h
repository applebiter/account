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

    const QString &getAvatar() const;
    const QString &getFullName() const;
    quint32 getId() const;
    const QString &getLongBiography() const;
    const QString &getShortBiography() const;
    quint32 getUserId() const;

public slots:

    void hydrate(QHash<QString, QVariant> &data);
    bool load(quint32 ident);
    bool save();
    void remove();

    void setAvatar(const QString &newAvatar);
    void setFullName(const QString &newFullName);
    void setId(quint32 newId);
    void setLongBiography(const QString &newLongBiography);
    void setShortBiography(const QString &newShortBiography);
    void setUserId(quint32 newUserId);

signals:

    void avatarChanged();
    void fullNameChanged();
    void idChanged();
    void longBiographyChanged();
    void shortBiographyChanged();
    void userIdChanged();

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
