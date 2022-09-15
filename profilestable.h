#ifndef PROFILESTABLE_H
#define PROFILESTABLE_H

#include <QList>
#include <QObject>
#include <QVariant>
#include "profile.h"

class ProfilesTable : public QObject
{
    Q_OBJECT

    public:

        explicit ProfilesTable(QObject *parent = nullptr);
        Profile* newEmptyProfile(QObject &a);
        Profile* newProfile(QObject &a, QHash<QString, QVariant> data);
        QList<Profile*> newProfiles(QObject &a, QHash<QString, QVariant> data, QHash<QString, QVariant> options);
        Profile* getProfile(QObject &a, quint32 id);
        Profile* patchProfile(Profile *profile, QHash<QString, QVariant> data);
        Profile* save(Profile *profile);
        QList<Profile*> saveMany(QList<Profile*> profiles, QHash<QString, QVariant> options);
        bool deleteProfile(Profile *profile);
        bool deleteProfiles(QList<Profile*> profiles);

    signals:

        void newProfileCreated();
        void newProfilesCreated();
        void profileFound();
        void profilePatched();
        void profileSaved();
        void profilesSaved();
        void profileDeleted();
        void profilesDeleted();
};

#endif // PROFILESTABLE_H
