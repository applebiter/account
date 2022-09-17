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
    void findByCode(QString code);
    void findByName(QString name);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // COUNTRIESTABLE_H
