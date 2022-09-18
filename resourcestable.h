#ifndef RESOURCESTABLE_H
#define RESOURCESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class ResourcesTable : public QObject
{
    Q_OBJECT

public:

    explicit ResourcesTable(QObject *parent = nullptr, const QString &descr = "");

    quint32 count(QSqlQuery &query);
    bool findByPath(QSqlQuery &query, QString path);
    bool findByType(QSqlQuery &query, QString type);
    const QString &descr() const;

public slots:

    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // RESOURCESTABLE_H
