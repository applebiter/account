#ifndef ZONE_H
#define ZONE_H

#include <QObject>

class Zone : public QObject
{
    Q_OBJECT
public:
    explicit Zone(QObject *parent = nullptr);

signals:

};

#endif // ZONE_H
