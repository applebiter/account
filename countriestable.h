#ifndef COUNTRIESTABLE_H
#define COUNTRIESTABLE_H

#include <QList>
#include <QObject>
#include <QVariant>
#include "country.h"

class CountriesTable : public QObject
{
    Q_OBJECT

public:

    explicit CountriesTable(QObject *parent = nullptr);
    Country* newEmptyCountry(QObject &a);
    Country* newCountry(QObject &a, QHash<QString, QVariant> data);
    QList<Country*> newCountries(QObject &a, QHash<QString, QVariant> data, QHash<QString, QVariant> options);
    Country* getCountry(QObject &a, quint32 id);
    Country* patchCountry(Country *country, QHash<QString, QVariant> data);
    Country* save(Country *country);
    QList<Country*> saveMany(QList<Country*> countries, QHash<QString, QVariant> options);
    bool deleteCountry(Country *country);
    bool deleteCountries(QList<Country*> countries);

signals:

    void newCountryCreated();
    void newCountriesCreated();
    void countryFound();
    void countryPatched();
    void countrySaved();
    void countriesSaved();
    void countryDeleted();
    void countriesDeleted();
};

#endif // COUNTRIESTABLE_H
