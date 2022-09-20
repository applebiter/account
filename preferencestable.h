#ifndef PREFERENCESTABLE_H
#define PREFERENCESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QSqlRelation>

class PreferencesTable : public QObject
{
    Q_OBJECT

public:

    explicit PreferencesTable(QObject *parent = nullptr);

    QSqlRelationalTableModel *getModel() const;

public slots:

private:

    QSqlDatabase db;
    QSqlRelationalTableModel *model;

private:

    void initializeModel();
};

#endif // PREFERENCESTABLE_H
