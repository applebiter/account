#ifndef OBJECTSTORE_H
#define OBJECTSTORE_H

#include <QObject>

class ObjectStore : public QObject
{
    Q_OBJECT
public:
    explicit ObjectStore(QObject *parent = nullptr);

signals:

};

#endif // OBJECTSTORE_H
