#include "appinternalstorage.h"

void AppInternalStorage::addElement(QString LibrePCBNetlist, QString SpiceNotation)
{
    QString name = "Netlist" + QString::number(counter++);
    ConversionData node(name, LibrePCBNetlist, SpiceNotation);
    storage.push_back(node);
    if (storage.size() > 5) {
        storage.pop_front();
    }
    currentElement = storage.size() - 1;
}

ConversionData AppInternalStorage::lastElement()
{
    currentElement = storage.size() - 1;
    return storage.empty() ? ConversionData() : storage.last();
}

ConversionData AppInternalStorage::nextElement()
{
    return currentElement < storage.size() - 1 ? storage[++currentElement] : ConversionData();
}

ConversionData AppInternalStorage::previousElement()
{
    return currentElement > 0 ? storage[--currentElement] : ConversionData();
}

AppInternalStorage::AppInternalStorage() {}

AppInternalStorage::~AppInternalStorage() {}
