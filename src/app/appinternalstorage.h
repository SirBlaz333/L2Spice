#ifndef APPINTERNALSTORAGE_H
#define APPINTERNALSTORAGE_H

#include <QList>
#include <src/conversion/data/conversiondata.h>

class AppInternalStorage
{
    int counter = 0;
    int currentElement;
    QList<ConversionData> storage;
public:
    void addElement(QString LibrePCBNetlist, QString SpiceNotation);
    ConversionData lastElement();
    ConversionData nextElement();
    ConversionData previousElement();
    AppInternalStorage();
    ~AppInternalStorage();
};

#endif // APPINTERNALSTORAGE_H
