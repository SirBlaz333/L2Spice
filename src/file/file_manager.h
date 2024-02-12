#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <QWidget>

class FileManager
{
public:
    static QString getOpenFileName(QWidget *parent = nullptr,
                                   QString path = QString(),
                                   QString filter = QString("All Files (*)"));
    static QString loadFile(QString fileName);
    static QString getSaveFileName(QWidget *parent = nullptr,
                                   QString fileName = QString(),
                                   QString path = QString(),
                                   QString filter = QString("All Files (*)"),
                                   bool forcedFileDialog = false);
    static bool save(QString fileName = QString(), QString data = QString());
    static bool confirmSaving(QString fileName, bool fileDialogWasShown = false);
    static QString getPath(QWidget *parent = nullptr, QString path = QString());
    static QString getFile(QWidget *parent = nullptr, QString path = QString());
};

#endif // FILE_MANAGER_H
