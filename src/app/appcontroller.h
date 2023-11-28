#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include "appstate.h"
#include "appinternalstorage.h"

#include <src/netlist/netlistparser.h>
#include <src/netlist/netlistproducer.h>
#include <src/netlist/netlistupdater.h>

class AppController
{
private:
    NetlistParser parser;
    NetlistProducer producer;
    NetlistUpdater updater;
    AppInternalStorage storage;

public:
    AppController();
    AppState convertToSpice(QString libreNotation,
                                               bool isSubcircuit,
                                               QString subcircuitName);
    AppState updateLibre(QString oldLibreNotation,
                                            QString newSpiceNotation);
    AppState previousSave();
    AppState nextSave();
    AppState lastSave();
};

#endif // APPCONTROLLER_H
