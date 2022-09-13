#ifndef USERSTABLE_H
#define USERSTABLE_H

#include <QObject>

class UsersTable : public QObject
{
    Q_OBJECT
public:
    explicit UsersTable(QObject *parent = nullptr);

signals:

};

#endif // USERSTABLE_H
