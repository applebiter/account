#ifndef ZONESTABLE_H
#define ZONESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class ZonesTable : public QObject
{
    Q_OBJECT

public:

    explicit ZonesTable(QObject *parent = nullptr, const QString &descr = "");
    quint32 count(QSqlQuery &query);
    bool findByCountryId(QSqlQuery &query, quint32 countryId);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // ZONESTABLE_H
