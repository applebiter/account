#ifndef PREFERENCESTABLE_H
#define PREFERENCESTABLE_H

#include <QList>
#include <QObject>
#include <QVariant>
#include "preference.h"

class PreferencesTable : public QObject
{
    Q_OBJECT

    public:

        explicit PreferencesTable(QObject *parent = nullptr);
        Preference* newEmptyPreference(QObject &a);
        Preference* newPreference(QObject &a, QHash<QString, QVariant> data);
        QList<Preference*> newPreferences(QObject &a, QHash<QString, QVariant> data, QHash<QString, QVariant> options);
        Preference* getPreference(QObject &a, quint32 id);
        Preference* patchPreference(Preference *preference, QHash<QString, QVariant> data);
        Preference* save(Preference *preference);
        QList<Preference*> saveMany(QList<Preference*> preferences, QHash<QString, QVariant> options);
        bool deletePreference(Preference *preference);
        bool deletePreferences(QList<Preference*> preferences);

    signals:

        void newPreferenceCreated();
        void newPreferencesCreated();
        void preferenceFound();
        void preferencePatched();
        void preferenceSaved();
        void preferencesSaved();
        void preferenceDeleted();
        void preferencesDeleted();
};

#endif // PREFERENCESTABLE_H
