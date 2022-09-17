#ifndef ZONE_H
#define ZONE_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class Zone : public QObject
{
    Q_OBJECT

public:

    explicit Zone(QObject *parent = nullptr, const QString &descr = "");
    void hydrate(QHash<QString, QVariant> data);
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

    quint32 getId() const;
    void setId(quint32 newId);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

signals:

    void countryIdChanged();
    void idChanged();
    void nameChanged();

public slots:

private:

    QString m_descr;
    quint32 countryId;
    quint32 id;
    QString name;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(quint32 countryId READ getCountryId WRITE setCountryId NOTIFY countryIdChanged)
    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
};

#endif // ZONE_H
