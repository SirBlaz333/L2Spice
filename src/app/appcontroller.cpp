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

QString AppController::saveFile(QWidget *parent,
                                QString fileName,
                                QString data,
                                bool forcedFileDialog)
{
    QString fileExtenstionFilter = "Circuit File (*.cir)";
    QString path = AppSettings::getSettings().value("DefaultDirectory").toString();
    fileName = FileManager::getSaveFileName(parent,
                                            fileName,
                                            path,
                                            fileExtenstionFilter,
                                            forcedFileDialog);
    FileManager::save(fileName, data);
    return fileName;
}

QString AppController::getOpenFileName(QWidget *parent)
{
    QString fileExtenstionFilter = "Circuit File (*.lp)";
    QString path = AppSettings::getSettings().value("DefaultDirectory").toString();
    return FileManager::getOpenFileName(parent, path, fileExtenstionFilter);
}

QString AppController::loadFile(QString fileName)
{
    return FileManager::loadFile(fileName);
}

void AppController::setLastSavedFile(QString lastSavedFile)
{
    this->lastSavedFile = lastSavedFile;
}

QString AppController::getLastSavedFile() const
{
    return lastSavedFile;
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
    return "/subcircuit/" + fileName + ".cir";
}
