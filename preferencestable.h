#ifndef PREFERENCESTABLE_H
#define PREFERENCESTABLE_H

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class PreferencesTable : public QObject
{
    Q_OBJECT

public:

    explicit PreferencesTable(QObject *parent = nullptr, const QString &descr = "");
    bool findByUserId(QSqlQuery &query, quint32 userId);

    const QString &descr() const;
    void setDescr(const QString &newDescr);

private:

    QString m_descr;

private:

    bool exec(QSqlQuery &query);
};

#endif // PREFERENCESTABLE_H
