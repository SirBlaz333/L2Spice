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
    return storage[++currentElement];
}

NetlistTemporaryStorageNode NetlistTemporaryStorage::previousElement()
{

    return storage[--currentElement];
}

bool NetlistTemporaryStorage::hasNextElement()
{
    return currentElement < storage.size() - 1;
}

bool NetlistTemporaryStorage::hasPreviousElement()
{
    return currentElement > 0;
}

NetlistTemporaryStorage::NetlistTemporaryStorage() {}

NetlistTemporaryStorage::~NetlistTemporaryStorage() {}
