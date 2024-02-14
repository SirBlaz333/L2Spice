#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <QWidget>

/**
 * FileManager is used to work with files and directories.
 */
class FileManager
{
public:
    /**
     * Opens the dialog to find the file to open for the given path and filter.
     * Opens the dialog in the current directory is the path is empty
     *
     * @param *parent - pointer to the parent QWidget.
     * @param path - the path where the dialog should be opened.
     * @param filter - file extension filter.
     * @return the name of the file to open.
     */
    static QString getOpenFileName(QWidget *parent = nullptr,
                                   QString path = QString(),
                                   QString filter = QString("All Files (*)"));

    /**
     * Reads the file and returns the text inside.
     *
     * @param fileName - the name of (the path to) the file.
     * @return the text inside the file.
     */
    static QString loadFile(QString fileName);

    /**
     * Opens the dialog to get the name of the file where the data should be saved.
     * Opens the dialog in the current directory is the path is empty.
     * If the name of the file and the path are specified and the file exists, just returns the absolute name of it.
     *
     * @param *parent - pointer to the parent QWidget.
     * @param fileName - the name of the file, if it exists.
     * @param path - the path where the dialog should be opened or the file located.
     * @param filter - file extension filter.
     * @param forcedFileDialog - when true forces opening of the dialog.
     * @return the name of the file to open.
     */
    static QString getSaveFileName(QWidget *parent = nullptr,
                                   QString fileName = QString(),
                                   QString path = QString(),
                                   QString filter = QString("All Files (*)"),
                                   bool forcedFileDialog = false);

    /**
     * Saves the given data in the diven name of the file.
     * Name of the file can be absolute or relative path.
     *
     * @param fileName - the name of the file.
     * @param data - data to save.
     * @return true if the file was saved successfully, false otherwise.
     */
    static bool save(QString fileName = QString(), QString data = QString());

    /**
     * Shows the save confirmation dialog if the file already exists.
     *
     * @param fileName - the name of the file.
     * @param fileDialogWasShown - whether the windows save dialog was shown before.
     * @return true if saving is confirmed, false otherwise.
     */
    static bool confirmSaving(QString fileName, bool fileDialogWasShown = false);

    /**
     * Open the dialog to get the path.
     *
     * @param *parent - pointer to the parent QWidget.
     * @param path - the default path where the searching should start.
     * @return the directory absolute path obtained during the dialog.
     */
    static QString getDir(QWidget *parent = nullptr, QString path = QString());

    /**
     * Open the dialog to get the file.
     *
     * @param *parent - pointer to the parent QWidget.
     * @param path - the default path where the searching should start.
     * @return the file absolute path obtained during the dialog.
     */
    static QString getFile(QWidget *parent = nullptr, QString path = QString());
};

#endif // FILE_MANAGER_H
