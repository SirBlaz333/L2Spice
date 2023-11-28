#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "src/file/filemanager.h"
#include "src/netlist/netlistparser.h"
#include "src/netlist/netlistproducer.h"
#include "src/netlist/netlisttemporarystorage.h"
#include "src/netlist/netlistupdater.h"

#include <QMainWindow>
#include <QSettings>

#include <src/app/appcontroller.h>

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

    void on_actionSave_subcircuit_triggered();

    void on_actionHome_directory_triggered();

private:
    AppController appController;
    FileManager fileManager;
    QString subcircuitName;
    bool canSaveSubcircuit;
    Ui::MainWindow *ui;
    void updateState(NetlistTemporaryStorageNode node);
    void save(bool forcedFileDialog);
};
#endif // MAINWINDOW_H
