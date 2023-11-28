#ifndef APPCONTROLLER_H
#define APPCONTROLLER_H

#include <src/netlist/netlistparser.h>
#include <src/netlist/netlistproducer.h>
#include <src/netlist/netlisttemporarystorage.h>
#include <src/netlist/netlistupdater.h>

class AppController
{
private:
    NetlistParser parser;
    NetlistProducer producer;
    NetlistUpdater updater;
    NetlistTemporaryStorage storage;

public:
    AppController();
    NetlistTemporaryStorageNode convertToSpice(QString libreNotation,
                                               bool isSubcircuit,
                                               QString subcircuitName);
    NetlistTemporaryStorageNode updateLibre(QString oldLibreNotation,
                                            QString newSpiceNotation);
    NetlistTemporaryStorageNode previousSave();
    NetlistTemporaryStorageNode nextSave();
    NetlistTemporaryStorageNode lastSave();
};

#endif // APPCONTROLLER_H
