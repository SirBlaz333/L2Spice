#include "mainwindow.h"
#include "homedirectorydialog.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->subcircuitNameLineEdit->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_convertToSpiceButton_clicked()
{
    QString libreNotation = ui->notationLibreTextEdit->toPlainText();
    bool isSubcircuit = ui->subcircuitCheckBox->isChecked();
    QString subcircuitName = ui->subcircuitNameLineEdit->text();
    AppState node = appController.convertToSpice(libreNotation, isSubcircuit, subcircuitName);
    ui->notationSpiceTextEdit->setPlainText(node.getSpiceNetlist());
    ui->nodeNameLabel->setText("Save name: " + node.getName());
}

void MainWindow::on_convertToLibreButton_clicked()
{
    QString libreNotation = ui->notationLibreTextEdit->toPlainText();
    QString spiceNotation = ui->notationSpiceTextEdit->toPlainText();
    AppState node = appController.updateLibre(libreNotation, spiceNotation);
    ui->notationLibreTextEdit->setPlainText(node.getLibrePCBNetlist());
    ui->nodeNameLabel->setText("Save name: " + node.getName());
}

void MainWindow::on_subcircuitCheckBox_stateChanged(int arg1)
{
    ui->subcircuitNameLineEdit->setVisible(arg1);
}

void MainWindow::on_actionNext_save_triggered()
{
    updateState(appController.nextSave());
}

void MainWindow::on_actionPrevious_save_triggered()
{
    updateState(appController.previousSave());
}

void MainWindow::on_actionLast_save_triggered()
{
    updateState(appController.lastSave());
}

void MainWindow::updateState(AppState node)
{
    if (node.isEmpty()) {
        return;
    }
    ui->notationLibreTextEdit->setText(node.getLibrePCBNetlist());
    ui->notationSpiceTextEdit->setText(node.getSpiceNetlist());
    ui->nodeNameLabel->setText("Save name: " + node.getName());
}

void MainWindow::save(bool forcedFileDialog)
{
    fileManager.save(this, ui->notationSpiceTextEdit->toPlainText(), "Circuit File (*.cir)", forcedFileDialog);
}

void MainWindow::on_actionSave_triggered()
{
    save(false);
}

void MainWindow::on_actionSave_As_triggered()
{
    save(true);
}


void MainWindow::on_actionSave_subcircuit_triggered()
{
    fileManager.saveSubcircuit(subcircuitName, ui->notationSpiceTextEdit->toPlainText());
}


void MainWindow::on_actionHome_directory_triggered()
{
    HomeDirectoryDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

