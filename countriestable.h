#ifndef COUNTRIESTABLE_H
#define COUNTRIESTABLE_H

#include <QObject>

class CountriesTable : public QObject
{
    Q_OBJECT
public:
    explicit CountriesTable(QObject *parent = nullptr);

signals:

};

#endif // COUNTRIESTABLE_H
