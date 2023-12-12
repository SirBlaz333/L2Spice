#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "appinternalstorage.h"
#include "appstate.h"

#include <src/netlist/netlistparser.h>
#include <src/netlist/netlistproducer.h>
#include <src/netlist/netlistupdater.h>
#include <src/file/filemanager.h>

#include <QWidget>

class AppController
{
private:
    NetlistParser parser;
    NetlistProducer producer;
    NetlistUpdater updater;
    AppInternalStorage storage;

public:
    AppController();
    ~AppController();
    AppState convertToSpice(QString libreNotation, bool isSubcircuit, QString subcircuitName);
    AppState updateLibre(QString oldLibreNotation, QString newSpiceNotation);
    QString saveSpice(QWidget* parent, QString fileName, QString data, bool forcedFileDialog = false);
    QString saveLibre(QWidget* parent, QString fileName, QString data, bool forcedFileDialog = false);
    QString getOpenFileName(QWidget *parent);
    QString loadFile(QString fileName);
    AppState previousSave();
    AppState nextSave();
    AppState lastSave();
    static QString getSubcircuitName(QString fileName);
};

#endif // APPCONTROLLER_H
