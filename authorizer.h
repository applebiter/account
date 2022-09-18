#ifndef AUTHORIZER_H
#define AUTHORIZER_H

#include <QObject>

class Authorizer : public QObject
{
    Q_OBJECT
public:
    explicit Authorizer(QObject *parent = nullptr);

signals:

};

#endif // AUTHORIZER_H
