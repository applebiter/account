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

    quint32 getId() const;
    const QString &getTheme() const;
    quint32 getUserId() const;

    const QHash<QString, QString> &getErrors() const;
    bool hasErrors();

public slots:

    void hydrate(QHash<QString, QVariant> &data);
    bool load(quint32 ident);
    bool save();
    void remove();

    void setId(quint32 newId);
    void setTheme(const QString &newTheme);
    void setUserId(quint32 newUserId);

    void clearErrors();

signals:

    void idChanged();
    void themeChanged();
    void userIdChanged();
    void errorOccurred();

private:

    quint32 id;
    QString theme;
    quint32 userId;
    QHash<QString, QString> errors;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
    Q_PROPERTY(QString theme READ getTheme WRITE setTheme NOTIFY themeChanged)
    Q_PROPERTY(quint32 userId READ getUserId WRITE setUserId NOTIFY userIdChanged)
};

#endif // PREFERENCE_H
