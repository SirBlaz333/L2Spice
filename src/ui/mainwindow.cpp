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
    Circuit circuit = parser.parseLibreNotation(libreNotation);
    QString name = ui->subcircuitNameLineEdit->text();
    circuit.setSubcircuitStatus(ui->subcircuitCheckBox->isChecked(), name == "" ? "DEFAULT_NAME" : name);
    if (circuit.getSubcircuitStatus()) {
        subcircuitName = circuit.getName();
    }
    QString spiceNotation = producer.produceSpiceNotationNetlist(circuit);
    ui->notationSpiceTextEdit->setPlainText(spiceNotation);
    storage.addElement(libreNotation, spiceNotation);
    ui->nodeNameLabel->setText("Save name: " + storage.lastElement().getName());
}

void MainWindow::on_convertToLibreButton_clicked()
{
    QString oldLibreNotation = ui->notationLibreTextEdit->toPlainText();
    QString newSpiceNotation = ui->notationSpiceTextEdit->toPlainText();
    QString oldSpiceNotation = storage.lastElement().getSpiceNetlist();
    QString newLibreNotation = updater.updateNetlist(oldLibreNotation, oldSpiceNotation, newSpiceNotation);
    ui->notationLibreTextEdit->setPlainText(newLibreNotation);
    storage.addElement(newLibreNotation, newSpiceNotation);
    ui->nodeNameLabel->setText("Save name: " + storage.lastElement().getName());
}

void MainWindow::on_subcircuitCheckBox_stateChanged(int arg1)
{
    ui->subcircuitNameLineEdit->setVisible(arg1);
}

void MainWindow::on_actionNext_save_triggered()
{
    if(storage.hasNextElement()) {
        NetlistTemporaryStorageNode node = storage.nextElement();
        updateState(node);
    }
}

void MainWindow::on_actionPrevious_save_triggered()
{
    if(storage.hasPreviousElement()) {
        NetlistTemporaryStorageNode node = storage.previousElement();
        updateState(node);
    }
}

void MainWindow::updateState(NetlistTemporaryStorageNode node)
{
    ui->notationLibreTextEdit->setText(node.getLibrePCBNetlist());
    ui->notationSpiceTextEdit->setText(node.getSpiceNetlist());
    ui->nodeNameLabel->setText("Save name: " + node.getName());
}

void MainWindow::on_actionLast_save_triggered()
{
    NetlistTemporaryStorageNode node = storage.lastElement();
    updateState(node);
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

