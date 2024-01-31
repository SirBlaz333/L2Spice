#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "appinternalstorage.h"

#include <src/conversion/data/conversionparams.h>
#include <src/conversion/librenetlistparser.h>
#include <src/conversion/librenetlistupdater.h>
#include <src/conversion/spicenetlistproducer.h>
#include <src/file/filemanager.h>

#include <QWidget>

class AppController
{
private:
    LibreNetlistParser parser;
    SpiceNetlistProducer producer;
    LibreNetlistUpdater updater;

public:
    AppController();
    ~AppController();
    QString convertToSpice(QString libreNotation, ConversionParams &params);
    QString updateLibre(QString oldLibreNotation, QString oldSpiceNotation, QString newSpiceNotation);
};

#endif // APPCONTROLLER_H
