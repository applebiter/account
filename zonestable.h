#ifndef ZONESTABLE_H
#define ZONESTABLE_H

#include <QObject>

class ZonesTable : public QObject
{
    Q_OBJECT
public:
    explicit ZonesTable(QObject *parent = nullptr);

signals:

};

#endif // ZONESTABLE_H
