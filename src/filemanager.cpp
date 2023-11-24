#include "../headers/filemanager.h"

#include <QFileDialog>

void FileManager::save(QWidget *parent, QString data, QString path, QString fileExtension, bool forcedFileDialog)
{
    if(forcedFileDialog || fileName.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(parent, "Save File", path, fileExtension);
    }

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
            QTextStream stream(&file);
            stream << data;
            file.close();
        }
    }
}

FileManager::FileManager() {}

FileManager::~FileManager() {}
