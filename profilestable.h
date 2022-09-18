#ifndef PROFILESTABLE_H
#define PROFILESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class ProfilesTable : public QObject
{
    Q_OBJECT

public:

    explicit ProfilesTable(QObject *parent = nullptr, const QString &descr = "");

    bool findByUserId(QSqlQuery &query, quint32 userId);
    const QString &descr() const;

public slots:

    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // PROFILESTABLE_H
