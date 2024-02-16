#include "app_controller.h"

#include <src/circuit/circuit.h>

QString AppController::convertToSpice(QString libreNetlist, ConversionParams &params)
{
    Circuit circuit = parser.parseLibreNotation(libreNetlist);
    if (!circuit.isEmpty()) {
        QString spiceNotation = producer.produceSpiceNetlist(circuit, params);
        updater.setSimulatorVersion(params.getSimulatorVersion());
        return spiceNotation;
    }
    return "";
}

QString AppController::updateLibre(QString libreNetlist, QString spiceNetlist)
{
    QString newLibreNotation = updater.updateNetlist(libreNetlist, spiceNetlist);
    return newLibreNotation;
}
