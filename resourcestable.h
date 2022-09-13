#ifndef RESOURCESTABLE_H
#define RESOURCESTABLE_H

#include <QObject>

class ResourcesTable : public QObject
{
    Q_OBJECT
public:
    explicit ResourcesTable(QObject *parent = nullptr);

signals:

};

#endif // RESOURCESTABLE_H
