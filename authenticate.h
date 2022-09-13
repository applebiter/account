#ifndef AUTHENTICATE_H
#define AUTHENTICATE_H

#include <QObject>

class Authenticate : public QObject
{
    Q_OBJECT
public:
    explicit Authenticate(QObject *parent = nullptr);

signals:

};

#endif // AUTHENTICATE_H
