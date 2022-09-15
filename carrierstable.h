#ifndef CARRIERSTABLE_H
#define CARRIERSTABLE_H

#include <QList>
#include <QObject>
#include <QVariant>
#include "carrier.h"

class CarriersTable : public QObject
{
    Q_OBJECT

public:

    explicit CarriersTable(QObject *parent = nullptr);
    Carrier* newEmptyCarrier(QObject &a);
    Carrier* newCarrier(QObject &a, QHash<QString, QVariant> data);
    QList<Carrier*> newCarriers(QObject &a, QHash<QString, QVariant> data, QHash<QString, QVariant> options);
    Carrier* getCarrier(QObject &a, quint32 id);
    Carrier* patchCarrier(Carrier *carrier, QHash<QString, QVariant> data);
    Carrier* save(Carrier *carrier);
    QList<Carrier*> saveMany(QList<Carrier*> carriers, QHash<QString, QVariant> options);
    bool deleteCarrier(Carrier *carrier);
    bool deleteCarriers(QList<Carrier*> carriers);

signals:

    void newCarrierCreated();
    void newCarriersCreated();
    void carrierFound();
    void carrierPatched();
    void carrierSaved();
    void carriersSaved();
    void carrierDeleted();
    void carriersDeleted();
};

#endif // CARRIERSTABLE_H
