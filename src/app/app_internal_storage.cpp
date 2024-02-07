#include "app_internal_storage.h"

AppState AppInternalStorage::addElement(QString libreNetlist,
                                        QString spiceNetlist,
                                        QString libreSourceFile,
                                        QString spiceSourceFile)
{
    QString name = "Netlist" + QString::number(counter++);
    AppState node(name, libreNetlist, spiceNetlist, libreSourceFile, spiceSourceFile);
    storage.push_back(node);
    if (storage.size() > maxSize) {
        storage.pop_front();
    }
    currentElementId = storage.size() - 1;
    return lastElement();
}

AppState AppInternalStorage::lastElement()
{
    currentElementId = storage.size() - 1;
    return storage.empty() ? AppState() : storage.last();
}

AppState AppInternalStorage::nextElement()
{
    return currentElementId < storage.size() - 1 ? storage[++currentElementId] : AppState();
}

AppState AppInternalStorage::previousElement()
{
    return currentElementId > 0 ? storage[--currentElementId] : AppState();
}

AppState AppInternalStorage::currentElement()
{
    return storage[currentElementId];
}

void AppInternalStorage::updateCurrentElement(AppState newState)
{
    storage[currentElementId] = newState;
}

AppInternalStorage::AppInternalStorage(const int &maxSize) : maxSize(maxSize) {}

AppInternalStorage::~AppInternalStorage() {}
