#include "appcontroller.h"
#include "appsettings.h"
#include "src/utils/regexutils.h"

#include <src/circuit/circuit.h>

AppController::AppController() {}

AppController::~AppController() {}

AppState AppController::convertToSpice(QString libreNotation, ConversionParams &params)
{
    Circuit circuit = parser.parseLibreNotation(libreNotation);
    if (!circuit.isEmpty()) {
        QString spiceNotation = producer.produceSpiceNotationNetlist(circuit, params);
        storage.addElement(libreNotation, spiceNotation);
    }
    return storage.lastElement();
}

AppState AppController::updateLibre(QString oldLibreNotation, QString newSpiceNotation)
{
    QString oldSpiceNotation = storage.lastElement().getSpiceNetlist();
    QString newLibreNotation = updater.updateNetlist(oldLibreNotation,
                                                     oldSpiceNotation,
                                                     newSpiceNotation);
    storage.addElement(newLibreNotation, newSpiceNotation);
    return storage.lastElement();
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
