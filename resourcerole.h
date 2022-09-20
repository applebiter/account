#ifndef RESOURCEROLE_H
#define RESOURCEROLE_H

#include <QObject>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>

class ResourceRole : public QObject
{
    Q_OBJECT

public:

    explicit ResourceRole(QObject *parent = nullptr);

    void begin();
    void commit();
    void rollback();
    bool open();
    void create();

    bool getCanCreate() const;
    bool getCanDelete() const;
    bool getCanExecute() const;
    bool getCanRead() const;
    bool getCanUpdate() const;
    const QString &getCreated() const;
    bool getIsOwner() const;
    const QString &getModified() const;
    quint32 getResourceId() const;
    quint32 getRoleId() const;
    quint32 getId() const;

public slots:

    void hydrate(QHash<QString, QVariant> &data);
    bool load(quint32 ident);
    bool save();
    void remove();

    void setCanCreate(bool newCanCreate);
    void setCanDelete(bool newCanDelete);
    void setCanExecute(bool newCanExecute);
    void setCanRead(bool newCanRead);
    void setCanUpdate(bool newCanUpdate);
    void setCreated(const QString &newCreated);
    void setId(quint32 newId);
    void setIsOwner(bool newIsOwner);
    void setModified(const QString &newModified);
    void setResourceId(quint32 newResourceId);
    void setRoleId(quint32 newRoleId);

signals:

    void canCreateChanged();
    void canDeleteChanged();
    void canExecuteChanged();
    void canReadChanged();
    void canUpdateChanged();
    void createdChanged();
    void isOwnerChanged();
    void modifiedChanged();
    void resourceIdChanged();
    void roleIdChanged();

    void idChanged();

private:

    bool canCreate;
    bool canDelete;
    bool canExecute;
    bool canRead;
    bool canUpdate;
    QString created;
    quint32 id;
    bool isOwner;
    QString modified;
    quint32 resourceId;
    quint32 roleId;

private:

    bool insert();
    bool update();
    bool exec(QSqlQuery &query);

    Q_PROPERTY(bool canCreate READ getCanCreate WRITE setCanCreate NOTIFY canCreateChanged)
    Q_PROPERTY(bool canDelete READ getCanDelete WRITE setCanDelete NOTIFY canDeleteChanged)
    Q_PROPERTY(bool canExecute READ getCanExecute WRITE setCanExecute NOTIFY canExecuteChanged)
    Q_PROPERTY(bool canRead READ getCanRead WRITE setCanRead NOTIFY canReadChanged)
    Q_PROPERTY(bool canUpdate READ getCanUpdate WRITE setCanUpdate NOTIFY canUpdateChanged)
    Q_PROPERTY(QString created READ getCreated WRITE setCreated NOTIFY createdChanged)
    Q_PROPERTY(bool isOwner READ getIsOwner WRITE setIsOwner NOTIFY isOwnerChanged)
    Q_PROPERTY(QString modified READ getModified WRITE setModified NOTIFY modifiedChanged)
    Q_PROPERTY(quint32 resourceId READ getResourceId WRITE setResourceId NOTIFY resourceIdChanged)
    Q_PROPERTY(quint32 roleId READ getRoleId WRITE setRoleId NOTIFY roleIdChanged)
    Q_PROPERTY(quint32 id READ getId WRITE setId NOTIFY idChanged)
};

#endif // RESOURCEROLE_H
