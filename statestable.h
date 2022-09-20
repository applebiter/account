#ifndef STATESTABLE_H
#define STATESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>

class StatesTable : public QObject
{
    Q_OBJECT

public:

    explicit StatesTable(QObject *parent = nullptr);

    quint32 count(QSqlQuery &query);
    bool findByCountryId(QSqlQuery &query, quint32 countryId);

    QSqlRelationalTableModel *getModel() const;

public slots:

private:

    QSqlDatabase db;
    QSqlRelationalTableModel *model;

private:

    void initializeModel();
};

#endif // STATESTABLE_H
