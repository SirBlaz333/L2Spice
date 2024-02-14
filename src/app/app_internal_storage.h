#ifndef APP_INTERNAL_STORAGE_H
#define APP_INTERNAL_STORAGE_H

#include "app_state.h"

#include <QList>

/**
 * AppInternalStorage is used to store the states of windowed application.
 * It can store LibrePCB circuit, SPICE notation and their file location if they exist.
 *
 */
class AppInternalStorage
{
    int counter = 0;
    int maxSize;
    int currentElementId;
    QList<AppState> storage;
public:
    /**
     * Adds the new element in the storage.
     *
     * @param librePCBNetlist - LibrePCB circuit.
     * @param spiceNetlist - SPICE netlist.
     * @param libreSourceFile - the file where LibrePCB circuit is stored.
     * @param spiceSourceFile - the file where SPICE netlist is stored.
     * @return last added instances of AppState.
     */
    AppState addElement(QString librePCBNetlist,
                        QString spiceNetlist,
                        QString libreSourceFile = QString(),
                        QString spiceSourceFile = QString());

    /**
     * @return last added element from the storage.
     */
    AppState lastElement();

    /**
     * @return next element from the storage.
     */
    AppState nextElement();

    /**
     * @return previous element from the storage.
     */
    AppState previousElement();

    /**
     * @return current element from the storage.
     */
    AppState currentElement();

    /**
     * Replaces current element to a new one.
     *
     * @param newState - new instance of AppState.
     */
    void updateCurrentElement(AppState newState);

    /**
     * @param maxSize - the max size of the storage.
     */
    AppInternalStorage(const int &maxSize);
};

#endif // APP_INTERNAL_STORAGE_H
