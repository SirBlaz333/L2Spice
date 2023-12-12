#include "appcontroller.h"
#include "appsettings.h"

#include <src/circuit/circuit.h>

AppController::AppController() {}

AppController::~AppController() {}

AppState AppController::convertToSpice(QString libreNotation,
                                       bool isSubcircuit,
                                       QString subcircuitName)
{
    Circuit circuit = parser.parseLibreNotation(libreNotation);
    if (!circuit.isEmpty()) {
        circuit.setSubcircuitStatus(isSubcircuit, subcircuitName);
        QString spiceNotation = producer.produceSpiceNotationNetlist(circuit);
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

QString saveFile(QWidget *parent,
                 QString fileName,
                 QString data,
                 QString fileExtensionFilter,
                 QString path,
                 bool forcedFileDialog)
{
    fileName = FileManager::getSaveFileName(parent,
                                            fileName,
                                            path,
                                            fileExtensionFilter,
                                            forcedFileDialog);
    FileManager::save(fileName, data);
    return fileName;
}

QString AppController::saveSpice(QWidget *parent,
                                 QString fileName,
                                 QString data,
                                 bool forcedFileDialog)
{
    return saveFile(parent,
                    fileName,
                    data,
                    "Circuit File (*.cir)",
                    AppSettings::getSpiceDir(),
                    forcedFileDialog);
}

QString AppController::saveLibre(QWidget *parent,
                                 QString fileName,
                                 QString data,
                                 bool forcedFileDialog)
{
    return saveFile(parent,
                    fileName,
                    data,
                    "Libre PCB Circuit File (*.lp)",
                    AppSettings::getLibreDir(),
                    forcedFileDialog);
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

QString AppController::getSubcircuitName(QString fileName)
{
    fileName = fileName.isEmpty() ? "DEFAULT" : fileName;
    return "/subcircuit/" + fileName + ".cir";
}
