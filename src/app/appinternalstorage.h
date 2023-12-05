#ifndef APPINTERNALSTORAGE_H
#define APPINTERNALSTORAGE_H

#include <QList>
#include <src/app/appstate.h>

class AppInternalStorage
{
    int counter = 0;
    int currentElement;
    QList<AppState> storage;
public:
    void addElement(QString LibrePCBNetlist, QString SpiceNotation);
    AppState lastElement();
    AppState nextElement();
    AppState previousElement();
    AppInternalStorage();
    ~AppInternalStorage();
};

#endif // APPINTERNALSTORAGE_H
