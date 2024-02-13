#include "app_controller.h"

#include <src/circuit/circuit.h>

AppController::AppController() {}

AppController::~AppController() {}

QString AppController::convertToSpice(QString libreNotation, ConversionParams &params)
{
    Circuit circuit = parser.parseLibreNotation(libreNotation);
    if (!circuit.isEmpty()) {
        QString spiceNotation = producer.produceSpiceNotationNetlist(circuit, params);
        updater.setSimulatorVersion(params.getSimulatorVersion());
        return spiceNotation;
    }
    return "";
}

QString AppController::updateLibre(QString oldLibreNotation, QString newSpiceNotation)
{
    QString newLibreNotation = updater.updateNetlist(oldLibreNotation, newSpiceNotation);
    return newLibreNotation;
}
