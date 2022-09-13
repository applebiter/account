#include "account.h"

Account::Account(QObject *parent)
    : QObject{parent}
{

}

bool Account::activateAccount()
{
    return true;
}

bool Account::changePassword()
{
    return true;
}

bool Account::login()
{
    return true;
}

bool Account::logout()
{
    return true;
}

bool Account::registerAccount()
{
    return true;
}

bool Account::resetPassword()
{
    return true;
}
