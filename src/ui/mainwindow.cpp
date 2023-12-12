#include "mainwindow.h"
#include "directorydialog.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->subcircuitNameLineEdit->setEnabled(false);
    ui->subcircuitSaveCheckbox->setEnabled(false);
    ui->actionSaveSubcircuit->setEnabled(false);
    ui->saveLibreButton->setProperty("class", "netlistStateButton");
    ui->refreshLibreButton->setProperty("class", "netlistStateButton");
    ui->clearLibreButton->setProperty("class", "netlistStateButton");
    ui->saveSpiceButton->setProperty("class", "netlistStateButton");
    ui->clearSpiceButton->setProperty("class", "netlistStateButton");
    ui->convertToSpiceButton->setProperty("class", "conversionButton");
    ui->convertToLibreButton->setProperty("class", "conversionButton");
    connect(ui->convertToSpiceButton, &QPushButton::clicked, this, &MainWindow::convertToSpice);
    connect(ui->convertToLibreButton, &QPushButton::clicked, this, &MainWindow::updateLibrePCB);
    connect(ui->subcircuitCheckBox,
            &QCheckBox::stateChanged,
            this,
            &MainWindow::subcircuitCheckBoxStateChanged);
    connect(ui->actionNextNetlist, &QAction::triggered, this, &MainWindow::nextNetlist);
    connect(ui->actionPreviousNetlist, &QAction::triggered, this, &MainWindow::previousNetlist);
    connect(ui->actionLastNetlist, &QAction::triggered, this, &MainWindow::lastNetlist);
    connect(ui->actionOpenDirDialog, &QAction::triggered, this, &MainWindow::openDirectoryDialog);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveSpice);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveSpiceAs);
    connect(ui->actionSaveSubcircuit, &QAction::triggered, this, &MainWindow::saveSubcircuit);
    connect(ui->saveSpiceButton, &QPushButton::clicked, this, &MainWindow::saveSpice);
    connect(ui->clearSpiceButton, &QPushButton::clicked, this, &MainWindow::closeSpice);
    connect(ui->actionOpenLibreNetlist, &QAction::triggered, this, &MainWindow::openLibre);
    connect(ui->actionSaveLibreNetlist, &QAction::triggered, this, &MainWindow::saveLibre);
    connect(ui->actionSaveLibrePCBNetlistAs, &QAction::triggered, this, &MainWindow::saveLibreAs);
    connect(ui->saveLibreButton, &QPushButton::clicked, this, &MainWindow::saveLibre);
    connect(ui->refreshLibreButton, &QPushButton::clicked, this, &MainWindow::refreshLibre);
    connect(ui->clearLibreButton, &QPushButton::clicked, this, &MainWindow::closeLibre);
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

void MainWindow::convertToSpice()
{
    try {
        QString libreNotation = ui->notationLibreTextEdit->toPlainText();
        bool isSubcircuit = ui->subcircuitCheckBox->isChecked();
        QString subcircuitName = ui->subcircuitNameLineEdit->text();
        AppState node = appController.convertToSpice(libreNotation, isSubcircuit, subcircuitName);
        ui->notationSpiceTextEdit->setPlainText(node.getSpiceNetlist());
        ui->netlistNameLabel->setText("Save name: " + node.getName());
        canSaveSubcircuit = ui->subcircuitCheckBox->isChecked();
        bool subcircuitState = ui->subcircuitCheckBox->isChecked()
                               && ui->subcircuitSaveCheckbox->isChecked();
        ui->actionSaveSubcircuit->setEnabled(subcircuitState);
        if (subcircuitState) {
            appController.saveSpice(this,
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

void MainWindow::updateLibrePCB()
{
    try {
        QString libreNotation = ui->notationLibreTextEdit->toPlainText();
        QString spiceNotation = ui->notationSpiceTextEdit->toPlainText();
        AppState node = appController.updateLibre(libreNotation, spiceNotation);
        ui->notationLibreTextEdit->setPlainText(node.getLibreNetlist());
        ui->netlistNameLabel->setText("Save name: " + node.getName());
    } catch (const std::exception &e) {
        QString message = e.what();
        qDebug() << message;
        showError(e, "Cannot update: " + message);
    }
}

void MainWindow::subcircuitCheckBoxStateChanged(int arg1)
{
    ui->subcircuitNameLineEdit->setEnabled(arg1);
    ui->subcircuitSaveCheckbox->setEnabled(arg1);
}

void MainWindow::nextNetlist()
{
    updateState(appController.nextSave());
}

void MainWindow::previousNetlist()
{
    updateState(appController.previousSave());
}

void MainWindow::lastNetlist()
{
    updateState(appController.lastSave());
}

void MainWindow::updateState(AppState node)
{
    if (node.isEmpty()) {
        return;
    }
    ui->notationLibreTextEdit->setText(node.getLibreNetlist());
    ui->notationSpiceTextEdit->setText(node.getSpiceNetlist());
    ui->netlistNameLabel->setText("Save name: " + node.getName());
}

void MainWindow::saveSpiceNetlist(bool forcedFileDialog)
{
    QString fileName = appController.saveSpice(this,
                                               ui->spiceFileLabel->text(),
                                               ui->notationSpiceTextEdit->toPlainText(),
                                               forcedFileDialog);
    ui->spiceFileLabel->setText(fileName);
}

void MainWindow::saveSpice()
{
    saveSpiceNetlist(true);
}

void MainWindow::saveSpiceAs()
{
    saveSpiceNetlist(false);
}

void MainWindow::saveSubcircuit()
{
    if (canSaveSubcircuit) {
        QString name = AppController::getSubcircuitName(ui->subcircuitNameLineEdit->text());
        appController.saveSpice(this, name, ui->notationSpiceTextEdit->toPlainText());
    }
}

void MainWindow::closeSpice()
{
    ui->notationSpiceTextEdit->setText("");
    ui->spiceFileLabel->setText("");
}

void MainWindow::saveLibreNetlist(bool forcedFileDialog)
{
    QString fileName = appController.saveLibre(this,
                                               ui->libreFileLabel->text(),
                                               ui->notationLibreTextEdit->toPlainText(),
                                               forcedFileDialog);
    ui->libreFileLabel->setText(fileName);
}

void MainWindow::saveLibre()
{
    saveLibreNetlist(false);
}

void MainWindow::saveLibreAs()
{
    saveLibreNetlist(true);
}

void MainWindow::openDirectoryDialog()
{
    DirectoryDialog dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::openLibre()
{
    QString libreFileName = appController.getOpenFileName(this);
    if (libreFileName.isEmpty()) {
        return;
    }
    QString data = appController.loadFile(libreFileName);
    ui->notationLibreTextEdit->setText(data);
    ui->libreFileLabel->setText(libreFileName);
}

void MainWindow::refreshLibre()
{
    QString data = appController.loadFile(ui->libreFileLabel->text());
    if (!data.isEmpty()) {
        ui->notationLibreTextEdit->setText(data);
    }
}

void MainWindow::closeLibre()
{
    ui->notationLibreTextEdit->setText("");
    ui->libreFileLabel->setText("");
}
