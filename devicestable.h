#ifndef DEVICESTABLE_H
#define DEVICESTABLE_H

#include <QObject>

class DevicesTable : public QObject
{
    Q_OBJECT
public:
    explicit DevicesTable(QObject *parent = nullptr);

signals:

};

#endif // DEVICESTABLE_H
