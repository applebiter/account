#ifndef PROFILESTABLE_H
#define PROFILESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>

class ProfilesTable : public QObject
{
    Q_OBJECT

public:

    explicit ProfilesTable(QObject *parent = nullptr);

    QSqlRelationalTableModel *getModel() const;

public slots:

private:

    QSqlDatabase db;
    QSqlRelationalTableModel *model;

private:

    void initializeModel();
};

#endif // PROFILESTABLE_H
