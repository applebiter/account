#ifndef DEVICESTABLE_H
#define DEVICESTABLE_H

#include <QList>
#include <QObject>
#include <QVariant>
#include "device.h"

class DevicesTable : public QObject
{
    Q_OBJECT

public:

    explicit DevicesTable(QObject *parent = nullptr);
    Device* newEmptyDevice(QObject &a);
    Device* newDevice(QObject &a, QHash<QString, QVariant> data);
    QList<Device*> newDevices(QObject &a, QHash<QString, QVariant> data, QHash<QString, QVariant> options);
    Device* getDevice(QObject &a, quint32 id);
    Device* patchDevice(Device *device, QHash<QString, QVariant> data);
    Device* save(Device *device);
    QList<Device*> saveMany(QList<Device*> devices, QHash<QString, QVariant> options);
    bool deleteDevice(Device *device);
    bool deleteDevices(QList<Device*> devices);

signals:

    void newDeviceCreated();
    void newDevicesCreated();
    void deviceFound();
    void devicePatched();
    void deviceSaved();
    void devicesSaved();
    void deviceDeleted();
    void devicesDeleted();
};

#endif // DEVICESTABLE_H
