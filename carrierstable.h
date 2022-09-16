#ifndef CARRIERSTABLE_H
#define CARRIERSTABLE_H

#include <QList>
#include <QObject>
#include <QSqlTableModel>
#include <QVariant>
#include "carrier.h"

class CarriersTable : public QObject
{
    Q_OBJECT

public:

    explicit CarriersTable(QObject *parent = nullptr);
    void findByCountryId(quint32 countryId);
    void findByName(QString name);

private:

    QSqlTableModel* model;
};

#endif // CARRIERSTABLE_H
