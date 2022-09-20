#ifndef RESOURCESTABLE_H
#define RESOURCESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>

class ResourcesTable : public QObject
{
    Q_OBJECT

public:

    explicit ResourcesTable(QObject *parent = nullptr);

    QSqlRelationalTableModel *getModel() const;

public slots:

private:

    QSqlDatabase db;
    QSqlRelationalTableModel *model;

private:

    void initializeModel();
};

#endif // RESOURCESTABLE_H
