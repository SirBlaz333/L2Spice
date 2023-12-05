#include "mainwindow.h"
#include "defaultdirectorydialog.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->subcircuitNameLineEdit->setEnabled(false);
    ui->subcircuitSaveCheckbox->setEnabled(false);
    ui->actionSave_subcircuit->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void showError(const std::exception &e, QString message)
{
    QMessageBox errorMessage;
    errorMessage.setIcon(QMessageBox::Critical);
    errorMessage.setWindowTitle("Error");
    errorMessage.setText(message);
    errorMessage.setMinimumWidth(150);
    errorMessage.addButton(QMessageBox::Ok);
    errorMessage.exec();
}

void MainWindow::on_convertToSpiceButton_clicked()
{
    try {
        QString libreNotation = ui->notationLibreTextEdit->toPlainText();
        bool isSubcircuit = ui->subcircuitCheckBox->isChecked();
        QString subcircuitName = ui->subcircuitNameLineEdit->text();
        AppState node = appController.convertToSpice(libreNotation, isSubcircuit, subcircuitName);
        ui->notationSpiceTextEdit->setPlainText(node.getSpiceNetlist());
        ui->nodeNameLabel->setText("Save name: " + node.getName());
        canSaveSubcircuit = ui->subcircuitCheckBox->isChecked();
        bool subcircuitState = ui->subcircuitCheckBox->isChecked()
                               && ui->subcircuitSaveCheckbox->isChecked();
        ui->actionSave_subcircuit->setEnabled(subcircuitState);
        if (subcircuitState) {
            appController.saveFile(this,
                                   appController.getSubcircuitName(subcircuitName),
                                   node.getSpiceNetlist(),
                                   false);
        }
    } catch (const std::exception &e) {
        QString message = e.what();
        qDebug() << message;
        showError(e, "Cannot convert: " + message);
    }
}

void MainWindow::on_convertToLibreButton_clicked()
{
    try {
        QString libreNotation = ui->notationLibreTextEdit->toPlainText();
        QString spiceNotation = ui->notationSpiceTextEdit->toPlainText();
        AppState node = appController.updateLibre(libreNotation, spiceNotation);
        ui->notationLibreTextEdit->setPlainText(node.getLibrePCBNetlist());
        ui->nodeNameLabel->setText("Save name: " + node.getName());
    } catch (const std::exception &e) {
        QString message = e.what();
        qDebug() << message;
        showError(e, "Cannot update: " + message);
    }
}

void MainWindow::on_subcircuitCheckBox_stateChanged(int arg1)
{
    ui->subcircuitNameLineEdit->setEnabled(arg1);
    ui->subcircuitSaveCheckbox->setEnabled(arg1);
}

void MainWindow::on_actionNextNetlist_triggered()
{
    updateState(appController.nextSave());
}

void MainWindow::on_actionPreviousNetlist_triggered()
{
    updateState(appController.previousSave());
}

void MainWindow::on_actionLastNetlist_triggered()
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
    QString lastSavedFile = appController.getLastSavedFile();
    lastSavedFile = appController.saveFile(this,
                                           lastSavedFile,
                                           ui->notationSpiceTextEdit->toPlainText(),
                                           forcedFileDialog);
    appController.setLastSavedFile(lastSavedFile);
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
    if (canSaveSubcircuit) {
        appController.saveFile(this,
                               AppController::getSubcircuitName(ui->subcircuitNameLineEdit->text()),
                               ui->notationSpiceTextEdit->toPlainText());
    }
}

void MainWindow::on_actionDefault_directory_triggered()
{
    DefaultDirectoryDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::on_actionOpen_LibrePCB_netlist_triggered()
{
    libreFileName = appController.getOpenFileName(this);
    QString data = appController.loadFile(libreFileName);
    ui->notationLibreTextEdit->setText(data);
    ui->libreLabel->setText(QString("LibrePCB (%1)").arg(libreFileName));
}

void MainWindow::on_pushButton_clicked()
{
    QString data = appController.loadFile(libreFileName);
    if (!data.isEmpty()) {
        ui->notationLibreTextEdit->setText(data);
    }
}
