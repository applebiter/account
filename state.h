#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class State : public QObject
{
    Q_OBJECT

public:

    explicit State(QObject *parent = nullptr);
    void begin();
    void commit();
    void rollback();
    bool open();
    void create();
    bool load(quint32 ident);
    bool save();
    void remove();

    const QString &getCode() const;
    void setCode(const QString &newCode);

    quint32 getCountryId() const;
    void setCountryId(quint32 newCountryId);

    quint32 getId() const;
    void setId(quint32 newId);

    const QString &getName() const;
    void setName(const QString &newName);

signals:

    void codeChanged();
    void countryIdChanged();
    void idChanged();
    void nameChanged();

public slots:

private:

    QString code;
    quint32 countryId;
    quint32 id;
    QString name;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(QString code READ getCode WRITE setCode NOTIFY codeChanged)
    Q_PROPERTY(quint32 countryId READ getCountryId WRITE setCountryId NOTIFY countryIdChanged)
    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString name READ getName WRITE setName NOTIFY nameChanged)
};

#endif // STATE_H
