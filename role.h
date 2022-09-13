#ifndef ROLE_H
#define ROLE_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class Role : public QObject
{
    Q_OBJECT

public:

    explicit Role(QObject *parent = nullptr);
    void begin();
    void commit();
    void rollback();
    bool open();
    void create();
    bool load(quint32 ident);
    bool save();
    void remove();

    quint32 getId() const;
    void setId(quint32 newId);

    const QString &getName() const;
    void setName(const QString &newName);

signals:

    void idChanged();
    void nameChanged();

public slots:

private:

    quint32 id;
    QString name;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
};

#endif // ROLE_H
