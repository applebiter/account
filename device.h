#ifndef DEVICE_H
#define DEVICE_H

#include <QDateTime>
#include <QDebug>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QtSql>
#include <QVariant>

class Device : public QObject
{
    Q_OBJECT

public:

    explicit Device(QObject *parent = nullptr);

    void begin();
    void commit();
    void rollback();
    bool open();
    void create();

    quint32 getCarrierId() const;
    const QString &getCreated() const;
    quint32 getId() const;
    const QString &getModified() const;
    const QString &getName() const;
    const QString &getNumber() const;
    quint32 getUserId() const;

public slots:

    void hydrate(QHash<QString, QVariant> &data);
    bool load(quint32 ident);
    bool save();
    void remove();

    void setCarrierId(quint32 newCarrierId);
    void setCreated(const QString &newCreated);
    void setId(quint32 newId);
    void setModified(const QString &newModified);
    void setName(const QString &newName);
    void setNumber(const QString &newNumber);
    void setUserId(quint32 newUserId);

    void clearErrors();

signals:

    void carrierIdChanged();
    void createdChanged();
    void idChanged();
    void modifiedChanged();
    void nameChanged();
    void numberChanged();
    void userIdChanged();
    void errorOccurred();

private:

    quint32 carrierId;
    QString created;
    quint32 id;
    QString modified;
    QString name;
    QString number;
    quint32 userId;
    QHash<QString, QString> errors;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(quint32 carrierId READ getCarrierId WRITE setCarrierId NOTIFY carrierIdChanged)
    Q_PROPERTY(QString created READ getCreated WRITE setCreated NOTIFY createdChanged)
    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString modified READ getModified WRITE setModified NOTIFY modifiedChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString number READ getNumber WRITE setNumber NOTIFY numberChanged)
    Q_PROPERTY(quint32 userId READ getUserId WRITE setUserId NOTIFY userIdChanged)
};

#endif // DEVICE_H
