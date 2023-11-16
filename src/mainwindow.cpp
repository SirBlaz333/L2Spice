#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->subciruitNameTextEdit->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Circuit circuit = parser.parseLibreNotation(
        ui->textEdit->toPlainText().toStdString());
    std::string name = ui->subciruitNameTextEdit->toPlainText().toStdString();
    circuit.setSubcircuitStatus(ui->checkBox->isChecked(), name == "" ? "DEFAULT_NAME" : name);
    spiceNotation = producer.produceSpiceNotationNetlist(circuit);
    ui->textEdit_2->setPlainText(QString::fromStdString(spiceNotation));
}


void MainWindow::on_pushButton_2_clicked()
{
    std::string textToUpdate = ui->textEdit->toPlainText().toStdString();
    std::string text = ui->textEdit_2->toPlainText().toStdString();
    std::string result = updater.updateNetlist(textToUpdate, spiceNotation, text);
    ui->textEdit->setPlainText(QString::fromStdString(result));
    spiceNotation = text;
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->subciruitNameTextEdit->setVisible(arg1);
}

