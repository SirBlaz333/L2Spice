#include "filemanager.h"

#include <QFileDialog>
#include <QSettings>
#include <qmessagebox.h>

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
    QFileInfo fileInfo(fileName);
    if (fileInfo.isAbsolute() && fileInfo.exists()) {
        return fileName;
    }
    return path = QDir(path).absoluteFilePath(fileName);;
}

bool FileManager::save(QString fileName, QString data)
{
    QFile file(fileName);
    if (!fileName.isEmpty() && file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream stream(&file);
        stream << data;
        file.close();
        return true;
    }
    return false;
}

bool FileManager::confirmSaving(QString fileName, bool fileDialogWasShown)
{
    if (!fileDialogWasShown && QFile::exists(fileName)) {
        QMessageBox::StandardButton reply =
            QMessageBox::question(nullptr,
                                  "File Exists",
                                  "The file already exists. Do you want to override it?",
                                  QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::No) {
            return false;
        }
    }
    return true;
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
