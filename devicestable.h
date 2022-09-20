#ifndef DEVICESTABLE_H
#define DEVICESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>

class DevicesTable : public QObject
{
    Q_OBJECT

public:

    explicit DevicesTable(QObject *parent = nullptr);

    QSqlRelationalTableModel *getModel() const;

public slots:

private:

    QSqlDatabase db;
    QSqlRelationalTableModel *model;

private:

    void initializeModel();
};

#endif // DEVICESTABLE_H
