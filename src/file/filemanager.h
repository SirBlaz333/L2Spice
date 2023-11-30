#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>

class FileManager
{
private:
    QString fileName;
public:
    void save(QWidget* parent, QString data, QString fileExtension, bool forcedFileDialog);
    static void saveSubcircuit(QString subcircuitName, QString data);
    static QString loadSubcircuit(QString subcircuitName);
    FileManager();
    ~FileManager();
};

#endif // FILEMANAGER_H
