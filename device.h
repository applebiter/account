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

    explicit Device(QObject *parent = nullptr, const QString &descr = "");
    void hydrate(QHash<QString, QVariant> data);
    void begin();
    void commit();
    void rollback();
    bool open();
    void create();
    bool load(quint32 ident);
    bool save();
    void remove();

    quint32 getCarrierId() const;
    void setCarrierId(quint32 newCarrierId);

    const QString &getCreated() const;
    void setCreated(const QString &newCreated);

    quint32 getId() const;
    void setId(quint32 newId);

    const QString &getModified() const;
    void setModified(const QString &newModified);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getNumber() const;
    void setNumber(const QString &newNumber);

    quint32 getUserId() const;
    void setUserId(quint32 newUserId);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

signals:

    void carrierIdChanged();
    void createdChanged();
    void idChanged();
    void modifiedChanged();
    void nameChanged();
    void numberChanged();
    void userIdChanged();

public slots:

private:

    QString m_descr;
    quint32 carrierId;
    QString created;
    quint32 id;
    QString modified;
    QString name;
    QString number;
    quint32 userId;

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
