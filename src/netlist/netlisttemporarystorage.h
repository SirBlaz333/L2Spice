#ifndef NETLISTTEMPORARYSTORAGE_H
#define NETLISTTEMPORARYSTORAGE_H

#include "netlisttemporarystoragenode.h"
#include <QList>

class NetlistTemporaryStorage
{
    int currentElement;
    QList<NetlistTemporaryStorageNode> storage;
public:
    void addElement(QString LibrePCBNetlist, QString SpiceNotation);
    NetlistTemporaryStorageNode lastElement();
    NetlistTemporaryStorageNode nextElement();
    NetlistTemporaryStorageNode previousElement();
    NetlistTemporaryStorage();
    ~NetlistTemporaryStorage();
};

#endif // NETLISTTEMPORARYSTORAGE_H
