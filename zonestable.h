#ifndef ZONESTABLE_H
#define ZONESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>

class ZonesTable : public QObject
{
    Q_OBJECT

public:

    explicit ZonesTable(QObject *parent = nullptr);

    QSqlRelationalTableModel *getModel() const;

public slots:

private:

    QSqlDatabase db;
    QSqlRelationalTableModel *model;

private:

    void initializeModel();
};

#endif // ZONESTABLE_H
