#include "carrierstable.h"

// temp hack to make the error messages go away until I've filled in stubs

CarriersTable::CarriersTable(QObject *parent)
    : QObject{parent}
{

}

Carrier *CarriersTable::newEmptyCarrier(QObject &a)
{
    Carrier *carrier = new Carrier(&a);
    return carrier;
}

Carrier *CarriersTable::newCarrier(QObject &a, QHash<QString, QVariant> data)
{
    Carrier *carrier = new Carrier(&a);
    return carrier;
}

QList<Carrier *> CarriersTable::newCarriers(QObject &a, QHash<QString, QVariant> data, QHash<QString, QVariant> options)
{
    QList<Carrier*> list;
    return list;
}

Carrier *CarriersTable::getCarrier(QObject &a, quint32 id)
{
    Carrier *carrier = new Carrier(&a);
    return carrier;
}

Carrier *CarriersTable::patchCarrier(Carrier *carrier, QHash<QString, QVariant> data)
{
    return carrier;
}

Carrier *CarriersTable::save(Carrier *carrier)
{
    return carrier;
}

QList<Carrier *> CarriersTable::saveMany(QList<Carrier *> carriers, QHash<QString, QVariant> options)
{
    QList<Carrier*> list;
    return list;
}

bool CarriersTable::deleteCarrier(Carrier *carrier)
{
    return true;
}

bool CarriersTable::deleteCarriers(QList<Carrier *> carriers)
{
    return true;
}
