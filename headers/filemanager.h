#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QWidget>



class FileManager
{
private:
    QString fileName;
public:
    void save(QWidget* parent, QString data, QString path, QString fileExtension, bool forcedFileDialog);
    FileManager();
    ~FileManager();
};

#endif // FILEMANAGER_H
