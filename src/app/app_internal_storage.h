#ifndef APP_INTERNAL_STORAGE_H
#define APP_INTERNAL_STORAGE_H

#include "app_state.h"

#include <QList>

class AppInternalStorage
{
    int counter = 0;
    int currentElementId;
    QList<AppState> storage;
public:
    AppState addElement(QString LibrePCBNetlist, QString SpiceNotation,
                    QString libreSourceFile = QString(), QString SpiceSourceFile = QString());
    AppState lastElement();
    AppState nextElement();
    AppState previousElement();
    AppState currentElement();
    void updateCurrentElement(AppState newState);
    AppInternalStorage();
    ~AppInternalStorage();
};

#endif // APP_INTERNAL_STORAGE_H
