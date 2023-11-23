#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->subcircuitNameTextEdit->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_convertToSpiceButton_clicked()
{
    QString libreNotation = ui->notationLibreTextEdit->toPlainText();
    Circuit circuit = parser.parseLibreNotation(libreNotation);
    QString name = ui->subcircuitNameTextEdit->toPlainText();
    circuit.setSubcircuitStatus(ui->subcircuitCheckBox->isChecked(), name == "" ? "DEFAULT_NAME" : name);
    QString spiceNotation = producer.produceSpiceNotationNetlist(circuit);
    ui->notationSpiceTextEdit->setPlainText(spiceNotation);
    storage.addElement(libreNotation, spiceNotation);
    ui->nodeNameLabel->setText(storage.lastElement().getName());
}


void MainWindow::on_convertToLibreButton_clicked()
{
    QString oldLibreNotation = ui->notationLibreTextEdit->toPlainText();
    QString newSpiceNotation = ui->notationSpiceTextEdit->toPlainText();
    QString oldSpiceNotation = storage.lastElement().getSpiceNetlist();
    QString newLibreNotation = updater.updateNetlist(oldLibreNotation, oldSpiceNotation, newSpiceNotation);
    ui->notationLibreTextEdit->setPlainText(newLibreNotation);
    storage.addElement(newLibreNotation, newSpiceNotation);
    ui->nodeNameLabel->setText(storage.lastElement().getName());
}


void MainWindow::on_subcircuitCheckBox_stateChanged(int arg1)
{
    ui->subcircuitNameTextEdit->setVisible(arg1);
}

void MainWindow::on_previousNodeButton_clicked()
{
    if(storage.hasPreviousElement()) {
        NetlistTemporaryStorageNode node = storage.previousElement();
        ui->notationLibreTextEdit->setText(node.getLibrePCBNetlist());
        ui->notationSpiceTextEdit->setText(node.getSpiceNetlist());
        ui->nodeNameLabel->setText(node.getName());
    }
}


void MainWindow::on_nextNodeButton_clicked()
{
    if(storage.hasNextElement()) {
        NetlistTemporaryStorageNode node = storage.nextElement();
        ui->notationLibreTextEdit->setText(node.getLibrePCBNetlist());
        ui->notationSpiceTextEdit->setText(node.getSpiceNetlist());
        ui->nodeNameLabel->setText(node.getName());
    }
}

