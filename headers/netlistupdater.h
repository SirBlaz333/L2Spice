#ifndef NETLISTUPDATER_H
#define NETLISTUPDATER_H

#include <QString>


class NetlistUpdater
{
public:
    NetlistUpdater();
    ~NetlistUpdater();
    QString updateNetlist(QString textToUpdate, QString oldVersion, QString newVersion);
};

#endif // NETLISTUPDATER_H
