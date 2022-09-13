#ifndef DEVICES_H
#define DEVICES_H

#include <QObject>

class Devices : public QObject
{
    Q_OBJECT
public:
    explicit Devices(QObject *parent = nullptr);

signals:

};

#endif // DEVICES_H
