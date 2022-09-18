#include "account.h"

Account::Account(QObject *parent, const QString &descr)
    : QObject{parent}, m_descr((descr))
{

}
