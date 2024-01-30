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
    AppInternalStorage storage;
    QString currentSource;

public:
    AppController();
    ~AppController();
    ConversionData convertToSpice(QString libreNotation, ConversionParams &params);
    ConversionData updateLibre(QString oldLibreNotation, QString newSpiceNotation);
    QString saveSpice(QWidget* parent, QString fileName, QString data, bool forcedFileDialog = false);
    QString saveLibre(QWidget* parent, QString fileName, QString data, bool forcedFileDialog = false);
    QString getOpenFileName(QWidget *parent);
    QString loadFile(QString fileName);
    ConversionData previousSave();
    ConversionData nextSave();
    ConversionData lastSave();
};

#endif // APPCONTROLLER_H
