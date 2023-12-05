#include "filemanager.h"

#include <QFileDialog>
#include <QSettings>

QString FileManager::getOpenFileName(QWidget *parent, QString path, QString filter)
{
    return QFileDialog::getOpenFileName(parent, "Open File", path, filter);
}

QString FileManager::loadFile(QString fileName)
{
    QFile file(fileName);
    if (!file.exists()) {
        return "";
    }
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "";
    }
    QTextStream in(&file);
    QString fileContents = in.readAll();
    file.close();
    return fileContents;
}

QString FileManager::getSaveFileName(QWidget *parent, QString fileName, QString path, QString filter, bool forcedFileDialog)
{
    if (forcedFileDialog || fileName.isEmpty()) {
        return QFileDialog::getSaveFileName(parent, "Open File", path, filter);
    }
    return path + fileName;
}

void FileManager::save(QString fileName, QString data)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream stream(&file);
        stream << data;
        file.close();
    }
}

FileManager::FileManager() {}

FileManager::~FileManager() {}
