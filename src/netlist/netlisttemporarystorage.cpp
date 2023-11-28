#include "netlisttemporarystorage.h"
#include "src/utils/uuidgenerator.h"

void NetlistTemporaryStorage::addElement(QString LibrePCBNetlist, QString SpiceNotation)
{
    QString name = uuid_generator::generateUUID();
    NetlistTemporaryStorageNode node(name, LibrePCBNetlist, SpiceNotation);
    storage.push_back(node);
    if (storage.size() > 5) {
        storage.pop_front();
    }
    currentElement = storage.size() - 1;
}

NetlistTemporaryStorageNode NetlistTemporaryStorage::lastElement()
{
    currentElement = storage.size() - 1;
    return storage.last();
}

NetlistTemporaryStorageNode NetlistTemporaryStorage::nextElement()
{
    return currentElement < storage.size() - 1 ? storage[++currentElement] : NetlistTemporaryStorageNode();
}

NetlistTemporaryStorageNode NetlistTemporaryStorage::previousElement()
{
    return currentElement > 0 ? storage[--currentElement] : NetlistTemporaryStorageNode();
}

NetlistTemporaryStorage::NetlistTemporaryStorage() {}

NetlistTemporaryStorage::~NetlistTemporaryStorage() {}
