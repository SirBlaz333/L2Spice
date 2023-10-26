#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Circuit circuit = parser.parseLibreNotation(
        ui->textEdit->toPlainText().toStdString());
    std::string spiceNotation = producer.produceSpiceNotationNetlist(circuit);
    ui->textEdit_2->setPlainText(QString::fromStdString(spiceNotation));
}

