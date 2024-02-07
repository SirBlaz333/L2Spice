#include "mainwindow.h"
#include "preferences_tabs.h"
#include "qregularexpression.h"
#include "src/utils/regex_utils.h"
#include "src/utils/global_variables.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDesktopServices>

#include <src/app/app_settings.h>

#include <src/file/file_manager.h>

Q_GLOBAL_STATIC(QString, EMPTY, QString());
Q_GLOBAL_STATIC(QUrl, USER_MANUAL_URL, QUrl::fromLocalFile("user_manual.pdf"));
Q_GLOBAL_STATIC(QUrl, LIBRE_PCB_URL, QUrl("https://librepcb.org/docs/"));
Q_GLOBAL_STATIC(QString, CIRCUIT_EXAMPLE, QString("example.lp"));
Q_GLOBAL_STATIC(QString, LIBRE_PCB_EXTENSION, QString("Libre PCB Circuit File (*.lp)"));
Q_GLOBAL_STATIC(QString, SPICE_EXTENSION, QString("Circuit File (*.cir)"));
Q_GLOBAL_STATIC(QString, CONVERSION_ERROR_EMPTY_NETLIST,
                QString("Cannot convert to SPICE netlist. Either the given LibrePCB netlist is empty or incorrect."));
Q_GLOBAL_STATIC(QString, CONVERSION_EXCEPTION, QString("Cannot convert: %1<br>LibrePCB circuit is incorrect"));
Q_GLOBAL_STATIC(QString, UPDATE_EXCEPTION, QString("Cannot update: %1"));
Q_GLOBAL_STATIC(QString, SAVE_NAME, QString("Save name: %1"));
Q_GLOBAL_STATIC(QString, SIMULATOR_EXECUTION_COMMAND, QString("%1 %2 > console_output.txt 2>&1"));
Q_GLOBAL_STATIC(QString, SIMULATOR_PATH_IS_EMPTY,
                QString("Cannot simulate the circuit. Please specify simulator path!"));
Q_GLOBAL_STATIC(QString, CIRCUIT_IS_EMPTY, QString("Cannot simulate the circuit. The circuit is empty!"));
Q_GLOBAL_STATIC(QString, CIRCUIT_IS_NOT_SAVED,
                QString("Cannot simulate the circuit. Please save the circuit first!"));
Q_GLOBAL_STATIC(QString, SIMULATION_IS_EXECUTED,
                QString("Simulation was executed. The results of the simulation are in the same directory "
                        "with circuit file. The console output is written into console_output.txt file."))

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
    ui->simulateButton->setProperty("class", "netlistStateButton");
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
    connect(ui->actionOpenPreferncesDialog, &QAction::triggered, this, &MainWindow::openDirectoryDialog);
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
    connect(ui->simulateButton, &QPushButton::clicked, this, &MainWindow::simulate);
    storage = new AppInternalStorage(AppSettings::getHistorySize());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void showMessage(QString message, QMessageBox::Icon icon, QString title)
{
    QMessageBox messageBox;
    messageBox.setIcon(icon);
    messageBox.setWindowTitle(title);
    messageBox.setText(message);
    messageBox.setMinimumWidth(150);
    messageBox.addButton(QMessageBox::Ok);
    messageBox.exec();
}

void showInfo(QString message)
{
    showMessage(message, QMessageBox::Information, "Info");
}

void showError(QString message)
{
    showMessage(message, QMessageBox::Critical, "Error");
}

void showWarning(QString message) {
    showMessage(message, QMessageBox::Warning, "Warning");
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
    bool fileDialogWasShown = forcedFileDialog || fileName.isEmpty();
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
        fileName = *EMPTY;
    }
    return saveFile(parent, fileName, data, *SPICE_EXTENSION, dir, forcedFileDialog);
}

void MainWindow::convertToSpice()
{
    try {
        QString libreNotation = ui->notationLibreTextEdit->toPlainText();
        ConversionParams params = getConversionParams();
        QString spiceNetlist = appController.convertToSpice(libreNotation, params);
        if (spiceNetlist.isEmpty()) {
            showWarning(*CONVERSION_ERROR_EMPTY_NETLIST);
            return;
        }
        spiceNetlist = header.getHeader(params, ui->libreFileLabel->text()) + spiceNetlist;
        ui->notationSpiceTextEdit->setHtml(spiceNetlist);
        saveSubcircuitIfNeeded(spiceNetlist, params);
        saveAndUpdateState();
    } catch (const std::exception &e) {
        QString message = e.what();
        qDebug() << message;
        showError(CONVERSION_EXCEPTION->arg(message));
    }
}

void MainWindow::updateLibrePCB()
{
    try {
        QString libreNotation = ui->notationLibreTextEdit->toPlainText();
        QString spiceNotation = ui->notationSpiceTextEdit->toPlainText();
        QString oldSpiceNotation = storage->lastElement().getSpiceNetlist();
        QString newLibreNotation = appController.updateLibre(libreNotation, oldSpiceNotation, spiceNotation);
        ui->notationLibreTextEdit->setPlainText(newLibreNotation);
        saveAndUpdateState();
    } catch (const std::exception &e) {
        QString message = e.what();
        qDebug() << message;
        showError(UPDATE_EXCEPTION->arg(message));
    }
}

ConversionParams MainWindow::getConversionParams()
{
    bool subcircuitStatus = ui->subcircuitCheckBox->isChecked();
    QString subcircuitName = ui->subcircuitNameLineEdit->text();
    bool fileOutput = ui->writeOutputInFilesCheckbox->isChecked();
    bool consoleOutput = ui->writeOutputOnConsoleCheckbox->isChecked();
    int converterVersion = ui->josimRadioButton->isChecked() ? SIMULATOR_VERSION_JOSIM
                                                             : SIMULATOR_VERSION_JSIM;
    lastParams = ConversionParams(subcircuitStatus,
                                  subcircuitName,
                                  fileOutput,
                                  consoleOutput,
                                  converterVersion);
    return lastParams;
}

void MainWindow::saveSubcircuitIfNeeded(QString subcircuit, ConversionParams params)
{
    QString subcircuitName = params.getSubcircuitName();
    bool saveSubcircuit = ui->subcircuitCheckBox->isChecked()
                          && ui->subcircuitSaveCheckbox->isChecked();
    if (saveSubcircuit) {
        subcircuitName = subcircuitName.isEmpty() ? "unnamed.cir" : subcircuitName + ".cir";
        QString fileName = saveSpiceFile(this, subcircuitName, subcircuit, false);
        ui->spiceFileLabel->setText(fileName);
    }
}

void MainWindow::saveAndUpdateState() {
    AppState state = storage->addElement(ui->notationLibreTextEdit->toHtml(),
                                         ui->notationSpiceTextEdit->toHtml(),
                                         ui->libreFileLabel->text(),
                                         ui->spiceFileLabel->text());
    ui->netlistNameLabel->setText(SAVE_NAME->arg(state.getName()));
}

void MainWindow::subcircuitCheckBoxStateChanged(int arg1)
{
    ui->subcircuitNameLineEdit->setEnabled(arg1);
    ui->subcircuitSaveCheckbox->setEnabled(arg1);
}

void MainWindow::nextNetlist()
{
    changeState(storage->nextElement());
}

void MainWindow::previousNetlist()
{
    changeState(storage->previousElement());
}

void MainWindow::lastNetlist()
{
    changeState(storage->lastElement());
}

void MainWindow::changeState(AppState state)
{
    if (state.isEmpty()) {
        return;
    }
    ui->libreFileLabel->setText(state.getLibreSourceFile());
    ui->spiceFileLabel->setText(state.getSpiceSourceFile());
    ui->notationLibreTextEdit->setText(state.getLibreNetlist());
    ui->notationSpiceTextEdit->setText(state.getSpiceNetlist());
    ui->netlistNameLabel->setText(SAVE_NAME->arg(state.getName()));
}



void MainWindow::saveSpiceNetlist(bool forcedFileDialog)
{
    QString fileName = ui->spiceFileLabel->text();
    QString data = ui->notationSpiceTextEdit->toPlainText();
    QString newFileName = saveSpiceFile(this, fileName, data, forcedFileDialog);
    ui->spiceFileLabel->setText(newFileName);
    AppState state = storage->currentElement();
    state.setSpiceSourceFile(newFileName);
    storage->updateCurrentElement(state);
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
    ui->notationSpiceTextEdit->setText(*EMPTY);
    ui->spiceFileLabel->setText(*EMPTY);
}

void MainWindow::saveLibreNetlist(bool forcedFileDialog)
{
    QString fileName = ui->libreFileLabel->text();
    QString data = ui->notationLibreTextEdit->toPlainText();
    fileName = saveFile(this, fileName, data, *LIBRE_PCB_EXTENSION, AppSettings::getLibreDir(), forcedFileDialog);
    ui->libreFileLabel->setText(fileName);
    AppState state = storage->currentElement();
    state.setLibreSourceFile(fileName);
    storage->updateCurrentElement(state);
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
    PreferencesTabs dialog;
    dialog.setModal(true);
    dialog.exec();
}

void MainWindow::openLibre()
{
    QString path = AppSettings::getLibreDir();
    QString libreFileName = FileManager::getOpenFileName(this, path, *LIBRE_PCB_EXTENSION);
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
    ui->notationLibreTextEdit->setText(*EMPTY);
    ui->libreFileLabel->setText(*EMPTY);
}

void MainWindow::openUserManual()
{
    QDesktopServices::openUrl(*USER_MANUAL_URL);
}

void MainWindow::openLibreDocumentation()
{
    QDesktopServices::openUrl(*LIBRE_PCB_URL);
}

void MainWindow::loadExample()
{
    ui->notationLibreTextEdit->setText(FileManager::loadFile(*CIRCUIT_EXAMPLE));
}

void MainWindow::simulate()
{
    QString simulator = lastParams.getSimulatorVersion() == SIMULATOR_VERSION_JOSIM
                            ? AppSettings::getJosimExecutablePath()
                            : AppSettings::getJsimExecutablePath();
    if (simulator.isEmpty()) {
        showWarning(*SIMULATOR_PATH_IS_EMPTY);
        return;
    }
    QString data = ui->notationSpiceTextEdit->toPlainText();
    if (data.isEmpty()) {
        showWarning(*CIRCUIT_IS_EMPTY);
        return;
    }
    QString fileName = ui->spiceFileLabel->text();
    if (fileName.isEmpty()) {
        fileName = saveSpiceFile(this, fileName, data, true);
    }
    if (fileName.isEmpty()) {
        showWarning(*CIRCUIT_IS_NOT_SAVED);
        return;
    }
    ui->spiceFileLabel->setText(fileName);
    std::string command = SIMULATOR_EXECUTION_COMMAND->arg(simulator, fileName).toStdString();
    system(command.c_str());
    showInfo(*SIMULATION_IS_EXECUTED);
}
