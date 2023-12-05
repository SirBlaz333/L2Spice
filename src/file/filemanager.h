#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>

class FileManager
{
public:
    static QString getOpenFileName(QWidget *parent = nullptr,
                                   QString path = QString(),
                                   QString filter = QString("All Files (*)"));
    static QString loadFile(QString fileName = QString());
    static QString getSaveFileName(QWidget *parent = nullptr,
                                   QString fileName = QString(),
                                   QString path = QString(),
                                   QString filter = QString("All Files (*)"),
                                   bool forcedFileDialog = false);
    static void save(QString fileName = QString(),
                        QString data = QString());
    FileManager();
    ~FileManager();
};

#endif // FILEMANAGER_H
