#include "file_manager.h"

#include <QFileDialog>
#include <QSettings>
#include <QTextStream>

#include <src/ui/notification_manager.h>

const QString CONFIRMATION_QUESTION = "The file already exists. Do you want to override it?";
const QString CONFIRMATION_TITLE = "File Exists";

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
        return NotificationManager::showQuestion(CONFIRMATION_QUESTION, CONFIRMATION_TITLE);
    }
    return true;
}

QString FileManager::getDir(QWidget *parent, QString path)
{
    path = QDir(path).exists() ? path : QDir::currentPath();
    QString directory = QFileDialog::getExistingDirectory(parent,
                                                          "Select directory",
                                                          path,
                                                          QFileDialog::ShowDirsOnly);
    return directory.isEmpty() ? path : directory;
}

QString FileManager::getFile(QWidget *parent, QString path)
{
    QString currentPath = QFile(path).exists() ? path : QDir::currentPath();
    QString directory = QFileDialog::getOpenFileName(parent, "Select file", currentPath);
    return directory.isEmpty() ? path : directory;
}
