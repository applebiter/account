#ifndef CARRIER_H
#define CARRIER_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class Carrier : public QObject
{
    Q_OBJECT

public:

    explicit Carrier(QObject *parent = nullptr);
    void begin();
    void commit();
    void rollback();
    bool open();
    void create();
    bool load(quint32 ident);
    bool save();
    void remove();

    quint32 getCountryId() const;
    void setCountryId(quint32 newCountryId);

    const QString &getGateway() const;
    void setGateway(const QString &newGateway);

    quint32 getId() const;
    void setId(quint32 newId);

    const QString &getName() const;
    void setName(const QString &newName);

signals:

    void countryIdChanged();
    void gatewayChanged();
    void idChanged();
    void nameChanged();

public slots:

private:

    quint32 countryId;
    QString gateway;
    quint32 id;
    QString name;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(quint32 countryId READ getCountryId WRITE setCountryId NOTIFY countryIdChanged)
    Q_PROPERTY(QString gateway READ getGateway WRITE setGateway NOTIFY gatewayChanged)
    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
};

#endif // CARRIER_H
