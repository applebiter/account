#ifndef COUNTRIESTABLE_H
#define COUNTRIESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class CountriesTable : public QObject
{
    Q_OBJECT

public:

    explicit CountriesTable(QObject *parent = nullptr, const QString &descr = "");
    bool findByCode(QSqlQuery &query, QString code);
    bool findByName(QSqlQuery &query, QString name);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // COUNTRIESTABLE_H
