#include "resourcerole.h"

ResourceRole::ResourceRole(QObject *parent)
    : QObject{parent}
{
    this->create();
}

void ResourceRole::hydrate(QHash<QString, QVariant> &data)
{
    if (data.contains("canCreate"))
    {
        this->canCreate = data["canCreate"].toBool();
    }
    if (data.contains("canDelete"))
    {
        this->canDelete = data["canDelete"].toBool();
    }
    if (data.contains("canExecute"))
    {
        this->canExecute = data["canExecute"].toBool();
    }
    if (data.contains("canRead"))
    {
        this->canRead = data["canRead"].toBool();
    }
    if (data.contains("canUpdate"))
    {
        this->canUpdate = data["canUpdate"].toBool();
    }
    if (data.contains("created"))
    {
        this->created = data["created"].toString();
    }
    if (data.contains("id"))
    {
        this->id = data["id"].toInt();
    }
    if (data.contains("isOwner"))
    {
        this->isOwner = data["isOwner"].toBool();
    }
    if (data.contains("modified"))
    {
        this->modified = data["modified"].toString();
    }
    if (data.contains("resourceId"))
    {
        this->resourceId = data["resourceId"].toInt();
    }
    if (data.contains("roleId"))
    {
        this->roleId = data["roleId"].toInt();
    }
}

void ResourceRole::begin()
{
    QSqlDatabase::database().transaction();
}

void ResourceRole::commit()
{
    QSqlDatabase::database().commit();
}

void ResourceRole::rollback()
{
    QSqlDatabase::database().rollback();
}

bool ResourceRole::open()
{
    QSqlDatabase db = QSqlDatabase::database();
    bool isOpen = db.isOpen();

    return isOpen;
}

void ResourceRole::create()
{
    this->canCreate = false;
    this->canDelete = false;
    this->canExecute = false;
    this->canRead = false;
    this->canUpdate = false;
    this->created = "";
    this->id = 0;
    this->isOwner = false;
    this->modified = "";
    this->resourceId = 0;
    this->roleId = 0;
}

bool ResourceRole::load(quint32 ident)
{
    QSqlQuery query;
    QString cmd = "SELECT can_create, can_delete, can_execute, can_read, can_update, created, id, is_owner, modified, resource_id, role_id FROM resources_roles where id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", ident);

    bool ok = this->exec(query);

    if (ok)
    {
        while (query.next())
        {
            QSqlRecord record = query.record();
            this->canCreate = record.value(0).toBool();
            this->canDelete = record.value(1).toBool();
            this->canExecute = record.value(2).toBool();
            this->canRead = record.value(3).toBool();
            this->canUpdate = record.value(4).toBool();
            this->created = record.value(5).toString();
            this->id = record.value(6).toBool();
            this->isOwner = record.value(7).toBool();
            this->modified = record.value(8).toString();
            this->resourceId = record.value(9).toInt();
            this->roleId = record.value(10).toInt();
        }
    }

    return ok;
}

bool ResourceRole::save()
{
    if (this->id > 0)
    {
        return this->update();
    }
    else
    {
        return this->insert();
    }
}

void ResourceRole::remove()
{
    QSqlQuery query;
    QString cmd = "DELETE FROM resources_roles WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":id", this->id);

    this->exec(query);
}

bool ResourceRole::getCanCreate() const
{
    return canCreate;
}

void ResourceRole::setCanCreate(bool newCanCreate)
{
    if (this->canCreate == newCanCreate)
        return;
    this->canCreate = newCanCreate;
    emit this->canCreateChanged();
}

bool ResourceRole::getCanDelete() const
{
    return this->canDelete;
}

void ResourceRole::setCanDelete(bool newCanDelete)
{
    if (this->canDelete == newCanDelete)
        return;
    this->canDelete = newCanDelete;
    emit this->canDeleteChanged();
}

bool ResourceRole::getCanExecute() const
{
    return this->canExecute;
}

void ResourceRole::setCanExecute(bool newCanExecute)
{
    if (this->canExecute == newCanExecute)
        return;
    this->canExecute = newCanExecute;
    emit this->canExecuteChanged();
}

bool ResourceRole::getCanRead() const
{
    return this->canRead;
}

void ResourceRole::setCanRead(bool newCanRead)
{
    if (this->canRead == newCanRead)
        return;
    this->canRead = newCanRead;
    emit this->canReadChanged();
}

bool ResourceRole::getCanUpdate() const
{
    return this->canUpdate;
}

void ResourceRole::setCanUpdate(bool newCanUpdate)
{
    if (this->canUpdate == newCanUpdate)
        return;
    this->canUpdate = newCanUpdate;
    emit this->canUpdateChanged();
}

const QString &ResourceRole::getCreated() const
{
    return this->created;
}

void ResourceRole::setCreated(const QString &newCreated)
{
    if (this->created == newCreated)
        return;
    this->created = newCreated.toUtf8();
    emit this->createdChanged();
}

bool ResourceRole::getIsOwner() const
{
    return this->isOwner;
}

void ResourceRole::setIsOwner(bool newIsOwner)
{
    if (this->isOwner == newIsOwner)
        return;
    this->isOwner = newIsOwner;
    emit this->isOwnerChanged();
}

const QString &ResourceRole::getModified() const
{
    return this->modified;
}

void ResourceRole::setModified(const QString &newModified)
{
    if (this->modified == newModified)
        return;
    this->modified = newModified.toUtf8();
    emit this->modifiedChanged();
}

quint32 ResourceRole::getResourceId() const
{
    return this->resourceId;
}

void ResourceRole::setResourceId(quint32 newResourceId)
{
    if (this->resourceId == newResourceId)
        return;
    this->resourceId = newResourceId;
    emit this->resourceIdChanged();
}

quint32 ResourceRole::getRoleId() const
{
    return this->roleId;
}

void ResourceRole::setRoleId(quint32 newRoleId)
{
    if (this->roleId == newRoleId)
        return;
    this->roleId = newRoleId;
    emit this->roleIdChanged();
}

quint32 ResourceRole::getId() const
{
    return this->id;
}

void ResourceRole::setId(quint32 newId)
{
    if (this->id == newId)
        return;
    this->id = newId;
    emit this->idChanged();
}

bool ResourceRole::insert()
{
    QSqlQuery query;
    QString cmd = "INSERT INTO resources_roles (can_create, can_delete, can_execute, can_read, can_update, created, is_owner, modified, resource_id, role_id) VALUES (:can_create, :can_delete, :can_execute, :can_read, :can_update, :created, :is_owner, :modified, :resource_id, :role_id);";
    query.prepare(cmd);
    query.bindValue(":can_create", this->canCreate);
    query.bindValue(":can_delete", this->canDelete);
    query.bindValue(":can_execute", this->canExecute);
    query.bindValue(":can_read", this->canRead);
    query.bindValue(":can_update", this->canUpdate);
    query.bindValue(":created", this->created);
    query.bindValue(":is_owner", this->isOwner);
    query.bindValue(":modified", this->modified);
    query.bindValue(":resource_id", this->resourceId);
    query.bindValue(":role_id", this->roleId);

    bool ok = exec(query);

    return ok;
}

bool ResourceRole::update()
{
    QSqlQuery query;
    QString cmd = "UPDATE resources_roles SET can_create = :can_create, can_delete = :can_delete, can_execute = :can_execute, can_read = :can_read, can_update = :can_update, created = :created, is_owner = :is_owner, modified = :modified, WHERE id = :id;";
    query.prepare(cmd);
    query.bindValue(":can_create", this->canCreate);
    query.bindValue(":can_delete", this->canDelete);
    query.bindValue(":can_execute", this->canExecute);
    query.bindValue(":can_read", this->canRead);
    query.bindValue(":can_update", this->canUpdate);
    query.bindValue(":created", this->created);
    query.bindValue(":is_owner", this->isOwner);
    query.bindValue(":modified", this->modified);
    query.bindValue(":id", this->id);

    bool ok = exec(query);

    return ok;
}

bool ResourceRole::exec(QSqlQuery &query)
{
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen())
    {
        return false;
    }

    //qInfo() << "Exec: " << query.executedQuery();
    bool ok =  query.exec();

    if (!ok)
    {
        qInfo() << db.lastError().text();
        qInfo() << query.lastError().text();
    }

    return ok;
}
