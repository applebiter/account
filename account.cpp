#include "account.h"

Account::Account(QObject *parent) : QObject{parent}
{
    this->isLoggedIn = false;
    this->authenticator = new Authenticator(this);
    this->authenticatedUser = this->authenticator->getAuthenticatedUser();
}

bool Account::hasErrors()
{
    if (this->errors.isEmpty())
    {
        return false;
    }

    return true;
}

User *Account::getAthenticatedUser() const
{
    return this->authenticatedUser;
}

bool Account::activateAccount(QString username, QString secret)
{
    User *newUser = new User(this);

    if (newUser->loadActivate(username, secret))
    {
        newUser->setIsActivated(true);
        newUser->setSecret("");
        newUser->save();
        newUser->commit();
    }
    else
    {
        User *staleUser = new User(this);

        if (staleUser->loadByUsername(username))
        {
            staleUser->remove();
            staleUser->commit();
            delete staleUser;
            this->errors.insert(QString("secret"), QString("The provided code was expired and the user account was deleted."));
        }
        else
        {
            this->errors.insert(QString("secret"), QString("There is no inactive account matching that username."));
        }
    }

    bool isActivated = newUser->getIsActivated();
    delete newUser;

    return isActivated;
}

bool Account::changePassword(QString currentPassword, QString newPassword)
{
    if (!this->isLoggedIn)
    {
        this->errors.insert(QString("password"), QString("You are not logged in and do not have permission to change any passwords."));
        return false;
    }

    QCryptographicHash *hash = new QCryptographicHash(QCryptographicHash::Sha512);
    hash->addData(this->authenticatedUser->getUuid().toUtf8());
    hash->addData(currentPassword.toUtf8());
    QString encodedPassword = hash->result().toBase64();

    if (QString::compare(this->authenticatedUser->getPassword(), encodedPassword) != 0)
    {
        this->errors.insert(QString("password"), QString("The value you entered for your current password is incorrect."));
        return false;
    }

    this->authenticatedUser->setPassword(newPassword);
    this->authenticatedUser->save();
    this->authenticatedUser->commit();

    return true;
}

void Account::clearErrors()
{
    this->errors.clear();
}

bool Account::login(QString username, QString password)
{
    this->isLoggedIn = this->authenticator->authenticate(username, password);

    if (this->isLoggedIn)
    {
        this->authenticatedUser = this->authenticator->getAuthenticatedUser();
    }
    else
    {
        this->errors.insert(QString("login"), QString("Login failed."));
    }

    return this->isLoggedIn;
}

void Account::logout()
{
    this->authenticator->clearAuthenticatedUser();
    this->authenticatedUser = this->authenticator->getAuthenticatedUser();
    this->isLoggedIn = false;
}

QString Account::getRandomString()
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
   const int randomStringLength = 12;

   QString randomString;
   for (int i = 0; i < randomStringLength; ++i)
   {
       int index = rand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }

   return randomString;
}

bool Account::registerAccount(QString username, QString email, QString password)
{
    User *newUser = new User(this);
    newUser->setEmail(email);
    newUser->setPassword(password);
    newUser->setSecret(this->getRandomString());
    newUser->setUsername(username);
    newUser->save();
    newUser->commit();

    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.beginGroup(QString("Mailer"));

    QString filename = settings.value("EmailActivationTemplate").toString();
    QFile file(filename);

    if (!file.exists())
    {
        this->errors.insert(QString("Mailer error:"), QString("The email activation template file was not found."));
        return false;
    }

    if (!file.open(QIODevice::ReadOnly))
    {
        this->errors.insert(QString("Filesystem error:"), QString(file.errorString()));
        return false;
    }

    QString contents = file.readAll();
    file.close();
    contents.replace("{{username}}", username);
    contents.replace("{{secret}}", newUser->getSecret());

    SimpleMail::Sender smtp(settings.value("Hostname").toString().toLatin1(), settings.value("Port").toInt(), SimpleMail::Sender::SslConnection);
    smtp.setUser(settings.value("Username").toString().toLatin1());
    smtp.setPassword(settings.value("Password").toString().toLatin1());

    SimpleMail::MimeMessage message;

    SimpleMail::EmailAddress sender(settings.value("SenderEmail").toString().toLatin1(), settings.value("SenderName").toString().toLatin1());
    message.setSender(sender);

    settings.endGroup();

    SimpleMail::EmailAddress to(email.toLatin1(), username.toLatin1());
    message.addTo(to);
    message.setSubject(QLatin1String("You successfully registered an account with RejackStudio"));

    auto text = new SimpleMail::MimeText;
    text->setText(contents.toLatin1());

    message.addPart(text);

    if (!smtp.sendMail(message))
    {
        this->errors.insert(QString("SMTP error:"), QString(smtp.lastError()));
        return false;
    }

    smtp.quit();

    return true;
}

bool Account::resetPassword1(QString username)
{

}

bool Account::resetPassword2(QString username, QString secret)
{

}

bool Account::getIsLoggedIn() const
{
    return this->isLoggedIn;
}

Authenticator *Account::getAuthenticator() const
{
    return this->authenticator;
}

const QHash<QString, QString> &Account::getErrors() const
{
    return this->errors;
}

