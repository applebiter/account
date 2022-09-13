#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "account_global.h"
#include <QObject>

class ACCOUNT_EXPORT Account : public QObject
{
    Q_OBJECT

public:

    explicit Account(QObject *parent = nullptr);
    bool activateAccount();
    bool changePassword();
    bool login();
    bool logout();
    bool registerAccount();
    bool resetPassword();

};
#endif // ACCOUNT_H
