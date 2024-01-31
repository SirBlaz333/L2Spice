#include "appcontroller.h"
#include "appsettings.h"
#include "src/utils/regexutils.h"

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

QString saveFile(QWidget *parent, QString fileName, QString data, QString fileExtensionFilter, QString path, bool forcedFileDialog)
{
    QString newFileName = FileManager::getSaveFileName(parent, fileName, path, fileExtensionFilter, forcedFileDialog);
    bool fileDialogWasShown = forcedFileDialog || (fileName != newFileName);
    if (!newFileName.isEmpty() && FileManager::confirmSaving(newFileName, fileDialogWasShown)) {
        FileManager::save(newFileName, data);
        return newFileName;
    }
    return fileName;
}

QString AppController::saveSpice(QWidget *parent, QString fileName, QString data, bool forcedFileDialog)
{
    QString dir = AppSettings::getSpiceDir();
    QRegularExpressionMatch match = RegexUtils::subcircuitRegex->match(data);
    if (match.hasMatch()) {
        dir = AppSettings::getSubcircuitDir();
        QString name = match.captured(1);
        fileName = dir + "/" + name + ".cir";
    } else if (fileName.contains(AppSettings::getSubcircuitDir())) {
        forcedFileDialog = true;
        fileName = "";
    }
    return saveFile(parent, fileName, data, "Circuit File (*.cir)", dir, forcedFileDialog);

}

QString AppController::saveLibre(QWidget *parent, QString fileName, QString data, bool forcedFileDialog)
{
    return saveFile(parent, fileName, data, "Libre PCB Circuit File (*.lp)", AppSettings::getLibreDir(), forcedFileDialog);
}

QString AppController::getOpenFileName(QWidget *parent)
{
    QString fileExtenstionFilter = "Libre PCB Circuit File (*.lp)";
    QString path = AppSettings::getLibreDir();
    return FileManager::getOpenFileName(parent, path, fileExtenstionFilter);
}

QString AppController::loadFile(QString fileName)
{
    return FileManager::loadFile(fileName);
}
