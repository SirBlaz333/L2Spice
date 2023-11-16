#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "netlistparser.h"
#include "netlistproducer.h"
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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    std::string spiceNotation;
    NetlistParser parser;
    NetlistProducer producer;
    NetlistUpdater updater;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
