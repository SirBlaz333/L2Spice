#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "filemanager.h"
#include "netlistparser.h"
#include "netlistproducer.h"
#include "netlisttemporarystorage.h"
#include "netlistupdater.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_convertToSpiceButton_clicked();

    void on_convertToLibreButton_clicked();

    void on_subcircuitCheckBox_stateChanged(int arg1);

    void on_actionNext_save_triggered();

    void on_actionPrevious_save_triggered();

    void on_actionLast_save_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

private:
    FileManager fileManager;
    NetlistParser parser;
    NetlistProducer producer;
    NetlistUpdater updater;
    NetlistTemporaryStorage storage;
    Ui::MainWindow *ui;
    void updateState(NetlistTemporaryStorageNode node);
    void save(bool forcedFileDialog);
};
#endif // MAINWINDOW_H
