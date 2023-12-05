#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void on_actionNextNetlist_triggered();

    void on_actionPreviousNetlist_triggered();

    void on_actionLastNetlist_triggered();

    void on_actionSave_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_subcircuit_triggered();

    void on_actionDefault_directory_triggered();

    void on_actionOpen_LibrePCB_netlist_triggered();

    void on_pushButton_clicked();

private:
    QString libreFileName;
    AppController appController;
    FileManager fileManager;
    bool canSaveSubcircuit;
    Ui::MainWindow *ui;
    void updateState(AppState node);
    void save(bool forcedFileDialog);
};
#endif // MAINWINDOW_H
