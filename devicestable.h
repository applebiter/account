#ifndef DEVICESTABLE_H
#define DEVICESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class DevicesTable : public QObject
{
    Q_OBJECT

public:

    explicit DevicesTable(QObject *parent = nullptr, const QString &descr = "");
    bool findByUserId(quint32 userId);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // DEVICESTABLE_H
