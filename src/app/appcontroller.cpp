#include "appcontroller.h"

#include <src/circuit/circuit.h>

AppController::AppController() {}

AppState AppController::convertToSpice(QString libreNotation,
                                                          bool isSubcircuit,
                                                          QString subcircuitName)
{
    Circuit circuit = parser.parseLibreNotation(libreNotation);
    circuit.setSubcircuitStatus(isSubcircuit, subcircuitName);
    QString spiceNotation = producer.produceSpiceNotationNetlist(circuit);
    storage.addElement(libreNotation, spiceNotation);
    return storage.lastElement();
}

AppState AppController::updateLibre(QString oldLibreNotation,
                                                       QString newSpiceNotation)
{
    QString oldSpiceNotation = storage.lastElement().getSpiceNetlist();
    QString newLibreNotation = updater.updateNetlist(oldLibreNotation,
                                                     oldSpiceNotation,
                                                     newSpiceNotation);
    storage.addElement(newLibreNotation, newSpiceNotation);
    return storage.lastElement();
}

AppState AppController::previousSave()
{
    return storage.previousElement();
}

AppState AppController::nextSave()
{
    return storage.nextElement();
}

AppState AppController::lastSave()
{
    return storage.lastElement();
}
