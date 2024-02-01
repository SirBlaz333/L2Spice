#include "mainwindow.h"
#include "preference_dialog.h"
#include "qregularexpression.h"
#include "src/utils/regex_utils.h"
#include "src/utils/global_variables.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDesktopServices>

#include <src/app/app_settings.h>

#include <src/file/file_manager.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->subcircuitNameLineEdit->setEnabled(false);
    ui->subcircuitSaveCheckbox->setEnabled(false);
    ui->writeOutputOnConsoleCheckbox->setChecked(true);
    ui->writeOutputInFilesCheckbox->setChecked(true);
    ui->josimRadioButton->setChecked(true);
    ui->netlistNameLabel->setProperty("class", "bold");
    ui->libreLabel->setProperty("class", "bold");
    ui->spiceLabel->setProperty("class", "bold");
    ui->subcircuitLabel->setProperty("class", "parameterPanelLabel");
    ui->outputLabel->setProperty("class", "parameterPanelLabel");
    ui->simulatorLabel->setProperty("class", "parameterPanelLabel");
    ui->saveLibreButton->setProperty("class", "netlistStateButton");
    ui->refreshLibreButton->setProperty("class", "netlistStateButton");
    ui->clearLibreButton->setProperty("class", "netlistStateButton");
    ui->saveSpiceButton->setProperty("class", "netlistStateButton");
    ui->clearSpiceButton->setProperty("class", "netlistStateButton");
    ui->convertToSpiceButton->setProperty("class", "conversionButton");
    ui->convertToLibreButton->setProperty("class", "conversionButton");
    ui->subcircuitFrame->setProperty("class", "conversionParameter");
    ui->outputFrame->setProperty("class", "conversionParameter");
    ui->versionFrame->setProperty("class", "conversionParameter");
    connect(ui->convertToSpiceButton, &QPushButton::clicked, this, &MainWindow::convertToSpice);
    connect(ui->convertToLibreButton, &QPushButton::clicked, this, &MainWindow::updateLibrePCB);
    connect(ui->subcircuitCheckBox,&QCheckBox::stateChanged, this,&MainWindow::subcircuitCheckBoxStateChanged);
    connect(ui->actionNextNetlist, &QAction::triggered, this, &MainWindow::nextNetlist);
    connect(ui->actionPreviousNetlist, &QAction::triggered, this, &MainWindow::previousNetlist);
    connect(ui->actionLastNetlist, &QAction::triggered, this, &MainWindow::lastNetlist);
    connect(ui->actionOpenDirDialog, &QAction::triggered, this, &MainWindow::openDirectoryDialog);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::saveSpice);
    connect(ui->actionSaveAs, &QAction::triggered, this, &MainWindow::saveSpiceAs);
    connect(ui->saveSpiceButton, &QPushButton::clicked, this, &MainWindow::saveSpice);
    connect(ui->clearSpiceButton, &QPushButton::clicked, this, &MainWindow::closeSpice);
    connect(ui->actionOpenLibreNetlist, &QAction::triggered, this, &MainWindow::openLibre);
    connect(ui->actionSaveLibreNetlist, &QAction::triggered, this, &MainWindow::saveLibre);
    connect(ui->actionSaveLibrePCBNetlistAs, &QAction::triggered, this, &MainWindow::saveLibreAs);
    connect(ui->saveLibreButton, &QPushButton::clicked, this, &MainWindow::saveLibre);
    connect(ui->refreshLibreButton, &QPushButton::clicked, this, &MainWindow::refreshLibre);
    connect(ui->clearLibreButton, &QPushButton::clicked, this, &MainWindow::closeLibre);
    connect(ui->actionUserManual, &QAction::triggered, this, &MainWindow::openUserManual);
    connect(ui->actionLibrePCBDocumenation, &QAction::triggered, this, &MainWindow::openLibreDocumentation);
    connect(ui->actionLoadExample, &QAction::triggered, this, &MainWindow::loadExample);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void showError(QString message)
{
    QMessageBox errorMessage;
    errorMessage.setIcon(QMessageBox::Critical);
    errorMessage.setWindowTitle("Error");
    errorMessage.setText(message);
    errorMessage.setMinimumWidth(150);
    errorMessage.addButton(QMessageBox::Ok);
    errorMessage.exec();
}

void showWarning(QString message) {
    QMessageBox warning;
    warning.setIcon(QMessageBox::Warning);
    warning.setWindowTitle("Warning");
    warning.setText(message);
    warning.setMinimumWidth(150);
    warning.addButton(QMessageBox::Ok);
    warning.exec();
}

QString saveFile(QWidget *parent,
                 QString fileName,
                 QString data,
                 QString fileExtensionFilter,
                 QString path,
                 bool forcedFileDialog)
{
    QString newFileName = FileManager::getSaveFileName(parent,
                                                       fileName,
                                                       path,
                                                       fileExtensionFilter,
                                                       forcedFileDialog);
    bool fileDialogWasShown = forcedFileDialog || (fileName != newFileName);
    if (!newFileName.isEmpty() && FileManager::confirmSaving(newFileName, fileDialogWasShown)) {
        FileManager::save(newFileName, data);
        return newFileName;
    }
    return fileName;
}

QString saveSpiceFile(QWidget *parent, QString fileName, QString data, bool forcedFileDialog)
{
    QString dir = AppSettings::getSpiceDir();
    QRegularExpressionMatch match = RegexUtils::subcircuitRegex->match(data);
    if (match.hasMatch()) {
        dir = AppSettings::getSubcircuitDir();
        QString name = match.captured(1);
        fileName = dir + "/" + name + ".cir";
    } else if (fileName.contains(AppSettings::getSubcircuitDir())) {
        forcedFileDialog = true;
        fileName = "";
    }
    return saveFile(parent, fileName, data, "Circuit File (*.cir)", dir, forcedFileDialog);
}

void MainWindow::convertToSpice()
{
    try {
        QString libreNotation = ui->notationLibreTextEdit->toPlainText();
        bool subcircuitStatus = ui->subcircuitCheckBox->isChecked();
        QString subcircuitName = ui->subcircuitNameLineEdit->text();
        bool fileOutput = ui->writeOutputInFilesCheckbox->isChecked();
        bool consoleOutput = ui->writeOutputOnConsoleCheckbox->isChecked();
        int converterVersion = ui->josimRadioButton->isChecked() ? SIMULATOR_VERSION_JOSIM
                                                                 : SIMULATOR_VERSION_JSIM;
        ConversionParams conversionParams(subcircuitStatus,
                                          subcircuitName,
                                          fileOutput,
                                          consoleOutput,
                                          converterVersion);
        QString spiceNetlist = header.getHeader(conversionParams, ui->libreFileLabel->text()) +
                               appController.convertToSpice(libreNotation, conversionParams);
        if (spiceNetlist.isEmpty()) {
            showWarning("Cannot convert to SPICE netlist. Either the given LibrePCB netlist is empty or incorrect.");
            return;
        }
        ui->notationSpiceTextEdit->setPlainText(spiceNetlist);
        bool subcircuitState = ui->subcircuitCheckBox->isChecked() && ui->subcircuitSaveCheckbox->isChecked();
        if (subcircuitState) {
            subcircuitName = subcircuitName.isEmpty() ? "unnamed.cir" : subcircuitName + ".cir";
            QString fileName = saveSpiceFile(this, subcircuitName, spiceNetlist, false);
            ui->spiceFileLabel->setText(fileName);
        }
        AppState state = generateNewState();
        ui->netlistNameLabel->setText("Save name: " + state.getName());
    } catch (const std::exception &e) {
        QString message = e.what();
        qDebug() << message;
        showError("Cannot convert: " + message + "\nLibrePCB circuit is incorrect");
    }
}

void MainWindow::updateLibrePCB()
{
    try {
        QString libreNotation = ui->notationLibreTextEdit->toPlainText();
        QString spiceNotation = ui->notationSpiceTextEdit->toPlainText();
        QString oldSpiceNotation = storage.lastElement().getSpiceNetlist();
        QString newLibreNotation = appController.updateLibre(libreNotation, oldSpiceNotation, spiceNotation);
        ui->notationLibreTextEdit->setPlainText(newLibreNotation);
        AppState state = generateNewState();
        ui->netlistNameLabel->setText("Save name: " + state.getName());
    } catch (const std::exception &e) {
        QString message = e.what();
        qDebug() << message;
        showError("Cannot update: " + message);
    }
}

void MainWindow::subcircuitCheckBoxStateChanged(int arg1)
{
    ui->subcircuitNameLineEdit->setEnabled(arg1);
    ui->subcircuitSaveCheckbox->setEnabled(arg1);
}

AppState MainWindow::generateNewState()
{
    return storage.addElement(ui->notationLibreTextEdit->toPlainText(),
                              ui->notationSpiceTextEdit->toPlainText(),
                              ui->libreFileLabel->text(),
                              ui->spiceFileLabel->text());
}

void MainWindow::nextNetlist()
{
    updateState(storage.nextElement());
}

void MainWindow::previousNetlist()
{
    updateState(storage.previousElement());
}

void MainWindow::lastNetlist()
{
    updateState(storage.lastElement());
}

void MainWindow::updateState(AppState state)
{
    if (state.isEmpty()) {
        return;
    }
    ui->libreFileLabel->setText(state.getLibreSourceFile());
    ui->spiceFileLabel->setText(state.getSpiceSourceFile());
    ui->notationLibreTextEdit->setText(state.getLibreNetlist());
    ui->notationSpiceTextEdit->setText(state.getSpiceNetlist());
    ui->netlistNameLabel->setText("Save name: " + state.getName());
}



void MainWindow::saveSpiceNetlist(bool forcedFileDialog)
{
    QString fileName = ui->spiceFileLabel->text();
    QString newFileName = saveSpiceFile(this,
                                    fileName,
                                    ui->notationSpiceTextEdit->toPlainText(),
                                    forcedFileDialog);
    ui->spiceFileLabel->setText(newFileName);
    AppState state = storage.currentElement();
    state.setSpiceSourceFile(newFileName);
    storage.updateCurrentElement(state);
}

void MainWindow::saveSpice()
{
    saveSpiceNetlist(false);
}

void MainWindow::saveSpiceAs()
{
    saveSpiceNetlist(true);
}

void MainWindow::closeSpice()
{
    ui->notationSpiceTextEdit->setText("");
    ui->spiceFileLabel->setText("");
}

void MainWindow::saveLibreNetlist(bool forcedFileDialog)
{
    QString fileName = saveFile(this,
                                ui->libreFileLabel->text(),
                                ui->notationLibreTextEdit->toPlainText(),
                                "Libre PCB Circuit File (*.lp)",
                                AppSettings::getLibreDir(),
                                forcedFileDialog);
    ui->libreFileLabel->setText(fileName);
    AppState state = storage.currentElement();
    state.setLibreSourceFile(fileName);
    storage.updateCurrentElement(state);
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
    QString fileExtenstionFilter = "Libre PCB Circuit File (*.lp)";
    QString path = AppSettings::getLibreDir();
    QString libreFileName = FileManager::getOpenFileName(this, path, fileExtenstionFilter);
    if (libreFileName.isEmpty()) {
        return;
    }
    QString data = FileManager::loadFile(libreFileName);
    ui->notationLibreTextEdit->setText(data);
    ui->libreFileLabel->setText(libreFileName);
}

void MainWindow::refreshLibre()
{
    QString data = FileManager::loadFile(ui->libreFileLabel->text());
    if (!data.isEmpty()) {
        ui->notationLibreTextEdit->setText(data);
    }
}

void MainWindow::closeLibre()
{
    ui->notationLibreTextEdit->setText("");
    ui->libreFileLabel->setText("");
}

void MainWindow::openUserManual()
{
    QString userManualPath = "user_manual.pdf";
    QUrl userManual = QUrl::fromLocalFile(userManualPath);
    QDesktopServices::openUrl(userManual);
}

void MainWindow::openLibreDocumentation()
{
    QDesktopServices::openUrl(QUrl("https://librepcb.org/docs/"));
}

void MainWindow::loadExample()
{
    ui->notationLibreTextEdit->setText(FileManager::loadFile("example.lp"));
}
