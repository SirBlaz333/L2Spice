#include "appcontroller.h"

#include <src/circuit/circuit.h>

AppController::AppController() {}

NetlistTemporaryStorageNode AppController::convertToSpice(QString libreNotation,
                                                          bool isSubcircuit,
                                                          QString subcircuitName)
{
    Circuit circuit = parser.parseLibreNotation(libreNotation);
    circuit.setSubcircuitStatus(isSubcircuit, subcircuitName);
    QString spiceNotation = producer.produceSpiceNotationNetlist(circuit);
    storage.addElement(libreNotation, spiceNotation);
    return storage.lastElement();
}

NetlistTemporaryStorageNode AppController::updateLibre(QString oldLibreNotation,
                                                       QString newSpiceNotation)
{
    QString oldSpiceNotation = storage.lastElement().getSpiceNetlist();
    QString newLibreNotation = updater.updateNetlist(oldLibreNotation,
                                                     oldSpiceNotation,
                                                     newSpiceNotation);
    storage.addElement(newLibreNotation, newSpiceNotation);
    return storage.lastElement();
}

NetlistTemporaryStorageNode AppController::previousSave()
{
    return storage.previousElement();
}

NetlistTemporaryStorageNode AppController::nextSave()
{
    return storage.nextElement();
}

NetlistTemporaryStorageNode AppController::lastSave()
{
    return storage.lastElement();
}
