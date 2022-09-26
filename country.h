#ifndef COUNTRY_H
#define COUNTRY_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class Country : public QObject
{
    Q_OBJECT

public:

    explicit Country(QObject *parent = nullptr);

    void begin();
    void commit();
    void rollback();
    bool open();
    void create();

    const QString &getCode() const;
    quint32 getId() const;
    const QString &getName() const;

    const QHash<QString, QString> &getErrors() const;
    bool hasErrors();

public slots:

    void hydrate(QHash<QString, QVariant> &data);
    bool load(quint32 ident);
    bool loadByCode(QString value);
    bool save();
    void remove();

    void setCode(const QString &newCode);
    void setId(quint32 newId);
    void setName(const QString &newName);

    void clearErrors();

signals:

    void codeChanged();
    void idChanged();
    void nameChanged();
    void errorOccurred();

private:

    QString code;
    quint32 id;
    QString name;
    QHash<QString, QString> errors;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(QString code READ getCode WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
};

#endif // COUNTRY_H
