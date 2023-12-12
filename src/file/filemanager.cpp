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
    if (QFile(fileName).exists()) {
        return fileName;
    }
    return path + fileName;
}

void FileManager::save(QString fileName, QString data)
{
    QDir dir = QFileInfo(fileName).absoluteDir();
    if (!dir.exists() && !dir.mkpath(".")) {
        qDebug() << "Failed to create directory: " << dir.path();
        return;
    }
    QFile file(fileName);
    if (!fileName.isEmpty() && file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream stream(&file);
        stream << data;
        file.close();
    }
}

QString FileManager::getPath(QWidget *parent, QString path)
{
    path = QDir(path).exists() ? path : QDir::currentPath();
    QString directory = QFileDialog::getExistingDirectory(parent,
                                                          "Select directory",
                                                          path,
                                                          QFileDialog::ShowDirsOnly);
    return directory.isEmpty() ? path : directory;
}

FileManager::FileManager() {}

FileManager::~FileManager() {}
