#ifndef STATESTABLE_H
#define STATESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class StatesTable : public QObject
{
    Q_OBJECT

public:

    explicit StatesTable(QObject *parent = nullptr);
    quint32 count(QSqlQuery &query);
    bool findByCountryId(QSqlQuery &query, quint32 countryId);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // STATESTABLE_H
