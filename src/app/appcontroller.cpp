#include "appcontroller.h"

#include <iomanip>
#include <src/circuit/circuit.h>

Q_GLOBAL_STATIC(QString, META_LINE, "*Converted %1 by L2Spice for %2 simulator.\n\n");

AppController::AppController() {}

AppController::~AppController() {}

QString getTime()
{
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeAsTimeT = std::chrono::system_clock::to_time_t(currentTime);
    std::tm *currentTimeAsTM = std::localtime(&currentTimeAsTimeT);
    std::ostringstream oss;
    oss << std::put_time(currentTimeAsTM, "%Y-%m-%d %H:%M:%S");
    return QString::fromStdString(oss.str());
}

QString getMetaInfo(ConversionParams &params)
{
    QString simulator = params.getConvertorVersion() == 1 ? "JoSIM" : "JSIM";
    return META_LINE->arg(getTime(), simulator);
}

QString AppController::convertToSpice(QString libreNotation, ConversionParams &params)
{
    Circuit circuit = parser.parseLibreNotation(libreNotation);
    if (!circuit.isEmpty()) {
        QString spiceNotation = getMetaInfo(params) +
                                producer.produceSpiceNotationNetlist(circuit, params);
        updater.setConvertorVersion(params.getConvertorVersion());
        return spiceNotation;
    }
    return "";
}

QString AppController::updateLibre(QString oldLibreNotation, QString oldSpiceNotation, QString newSpiceNotation)
{
    QString newLibreNotation = updater.updateNetlist(oldLibreNotation,
                                                     oldSpiceNotation,
                                                     newSpiceNotation);
    return newLibreNotation;
}

