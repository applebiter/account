#ifndef RESOURCE_H
#define RESOURCE_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class Resource : public QObject
{
    Q_OBJECT

public:

    explicit Resource(QObject *parent = nullptr);

    void begin();
    void commit();
    void rollback();
    bool open();
    void create();

    quint32 getId() const;
    const QString &getPath() const;
    const QString &getType() const;

public slots:

    void hydrate(QHash<QString, QVariant> &data);
    bool load(quint32 ident);
    bool save();
    void remove();

    void setId(quint32 newId);
    void setPath(const QString &newPath);
    void setType(const QString &newType);

signals:

    void idChanged();
    void pathChanged();
    void typeChanged();

private:

    quint32 id;
    QString path;
    QString type;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString path READ getPath WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(QString type READ getType WRITE setType NOTIFY typeChanged)
};

#endif // RESOURCE_H
