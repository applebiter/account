#include "account.h"

Account::Account(QObject *parent)
    : QObject{parent}
{

}

bool Account::registerAccount(QString username, QString email, QString password)
{
    SimpleMail::Sender smtp(QLatin1String("smtp.dreamhost.com"), 465, SimpleMail::Sender::SslConnection);
    smtp.setUser(QLatin1String("rejackserver@applebiter.com"));
    smtp.setPassword(QLatin1String("4bE2HTek"));

    SimpleMail::MimeMessage message;
    SimpleMail::EmailAddress sender(QLatin1String("rejackserver@applebiter.com"), QLatin1String("ReJack Server"));
    message.setSender(sender);
    SimpleMail::EmailAddress to(QLatin1String("webmaster@applebiter.com"), QLatin1String("Webmaster"));
    message.addTo(to);
    message.setSubject(QLatin1String("You successfully registered an account with RejackStudio"));

    auto text = new SimpleMail::MimeText;
    text->setText(QLatin1String("Your account was created but you will be unable to log in until you have activated it. Use this code to activate your account and login:\n"));

    message.addPart(text);

    if (!smtp.sendMail(message))
    {
        false;
    }

    smtp.quit();

    return true;
}
