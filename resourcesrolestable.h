#ifndef RESOURCESROLESTABLE_H
#define RESOURCESROLESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class ResourcesRolesTable : public QObject
{
    Q_OBJECT

public:

    explicit ResourcesRolesTable(QObject *parent = nullptr, const QString &descr = "");
    bool findByResourceId(QSqlQuery &query, quint32 resourceId);
    bool findByRoleId(QSqlQuery &query, quint32 roleId);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // RESOURCESROLESTABLE_H
