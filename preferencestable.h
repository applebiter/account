#ifndef PREFERENCESTABLE_H
#define PREFERENCESTABLE_H

#include <QObject>

class PreferencesTable : public QObject
{
    Q_OBJECT
public:
    explicit PreferencesTable(QObject *parent = nullptr);

signals:

};

#endif // PREFERENCESTABLE_H
