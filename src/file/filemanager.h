#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>

class FileManager
{
private:
    QString fileName;
public:
    void save(QWidget* parent, QString data, QString fileExtension, bool forcedFileDialog);
    void saveSubcircuit(QString fileName, QString data);
    FileManager();
    ~FileManager();
};

#endif // FILEMANAGER_H
