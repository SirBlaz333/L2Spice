#ifndef NETLISTUPDATER_H
#define NETLISTUPDATER_H

#include <string>

class NetlistUpdater
{
public:
    NetlistUpdater();
    ~NetlistUpdater();
    std::string updateNetlist(std::string textToUpdate, std::string oldVersion, std::string newVersion);
};

#endif // NETLISTUPDATER_H
