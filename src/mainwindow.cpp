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
    Circuit circuit = parser.parseLibreNotation(ui->textEdit->toPlainText());
    QString name = ui->subciruitNameTextEdit->toPlainText();
    circuit.setSubcircuitStatus(ui->checkBox->isChecked(), name == "" ? "DEFAULT_NAME" : name);
    spiceNotation = producer.produceSpiceNotationNetlist(circuit);
    ui->textEdit_2->setPlainText(spiceNotation);
}


void MainWindow::on_pushButton_2_clicked()
{
    QString textToUpdate = ui->textEdit->toPlainText();
    QString text = ui->textEdit_2->toPlainText();
    QString result = updater.updateNetlist(textToUpdate, spiceNotation, text);
    ui->textEdit->setPlainText(result);
    spiceNotation = text;
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    ui->subciruitNameTextEdit->setVisible(arg1);
}

