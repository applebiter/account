#ifndef ROLESTABLE_H
#define ROLESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class RolesTable : public QObject
{
    Q_OBJECT

public:

    explicit RolesTable(QObject *parent = nullptr, const QString &descr = "");
    quint32 count(QSqlQuery &query);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // ROLESTABLE_H
