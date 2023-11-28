#include "appinternalstorage.h"
#include "src/utils/uuidgenerator.h"

void AppInternalStorage::addElement(QString LibrePCBNetlist, QString SpiceNotation)
{
    QString name = uuid_generator::generateUUID();
    AppState node(name, LibrePCBNetlist, SpiceNotation);
    storage.push_back(node);
    if (storage.size() > 5) {
        storage.pop_front();
    }
    currentElement = storage.size() - 1;
}

AppState AppInternalStorage::lastElement()
{
    currentElement = storage.size() - 1;
    return storage.last();
}

AppState AppInternalStorage::nextElement()
{
    return currentElement < storage.size() - 1 ? storage[++currentElement] : AppState();
}

AppState AppInternalStorage::previousElement()
{
    return currentElement > 0 ? storage[--currentElement] : AppState();
}

AppInternalStorage::AppInternalStorage() {}

AppInternalStorage::~AppInternalStorage() {}
