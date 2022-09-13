#ifndef PREFERENCE_H
#define PREFERENCE_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class Preference : public QObject
{
    Q_OBJECT

public:

    explicit Preference(QObject *parent = nullptr);
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

    const QString &getTheme() const;
    void setTheme(const QString &newTheme);

    quint32 getUserId() const;
    void setUserId(quint32 newUserId);

signals:

    void idChanged();
    void themeChanged();
    void userIdChanged();

public slots:

private:

    quint32 id;
    QString theme;
    quint32 userId;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString theme READ getTheme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(quint32 userId READ getUserId WRITE setUserId NOTIFY userIdChanged)
};

#endif // PREFERENCE_H
