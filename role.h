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

    quint32 getId() const;
    const QString &getName() const;

    const QHash<QString, QString> &getErrors() const;
    bool hasErrors();

public slots:

    void hydrate(QHash<QString, QVariant> &data);
    bool load(quint32 ident);
    bool loadByName(QString value);
    bool save();
    void remove();

    void setId(quint32 newId);
    void setName(const QString &newName);

    void clearErrors();

signals:

    void idChanged();
    void nameChanged();
    void errorOccurred();

private:

    quint32 id;
    QString name;
    QHash<QString, QString> errors;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
};

#endif // ROLE_H
