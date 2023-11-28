#include "filemanager.h"

#include <QFileDialog>
#include <QSettings>

#include <src/app/appsettings.h>

void writeToFile(QString fileName, QString data) {
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QTextStream stream(&file);
            stream << data;
            file.close();
        }
    }
}

void FileManager::save(QWidget *parent, QString data, QString fileExtension, bool forcedFileDialog)
{
    QString path = AppSettings::getSettings().value("HomeDirectory").toString();
    if(forcedFileDialog || fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(parent, "Save File", path, fileExtension);
    }
    writeToFile(fileName, data);
}

void FileManager::saveSubcircuit(QString fileName, QString data)
{
    QString path = AppSettings::getSettings().value("HomeDirectory").toString();
    QDir dir(path + "/subcircuit");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    QString filePath = dir.filePath(fileName + ".cir");
    writeToFile(filePath, data);
}

FileManager::FileManager() {}

FileManager::~FileManager() {}
