#ifndef CARRIERSTABLE_H
#define CARRIERSTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class CarriersTable : public QObject
{
    Q_OBJECT

public:

    explicit CarriersTable(QObject *parent = nullptr, const QString &descr = "");
    void findByCountryId(quint32 countryId);
    void findByName(QString name);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // CARRIERSTABLE_H
