#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

    void on_previousNodeButton_clicked();

    void on_nextNodeButton_clicked();

private:
    NetlistParser parser;
    NetlistProducer producer;
    NetlistUpdater updater;
    NetlistTemporaryStorage storage;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
