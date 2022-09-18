#ifndef USERSTABLE_H
#define USERSTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class UsersTable : public QObject
{
    Q_OBJECT

public:

    explicit UsersTable(QObject *parent = nullptr, const QString &descr = "");

    quint32 count(QSqlQuery &query);
    bool findByIsActivated(QSqlQuery &query, bool isActivated);
    bool findByRoleId(QSqlQuery &query, quint32 roleId);

    const QString &descr() const;

public slots:

    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // USERSTABLE_H
