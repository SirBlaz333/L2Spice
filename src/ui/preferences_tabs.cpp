#include "preferences_tabs.h"
#include "notification_manager.h"
#include "ui_preferences.h"

#include <QFileDialog>
#include <QSettings>

#include <src/app/app_settings.h>
#include <src/file/file_manager.h>

const QString CHANGES_MESSAGE = "Changes have been made to a setting (History size) that requires "
                                "a program restart to take effect. Please "
                                "restart the program for the changes to be applied.";

const QRegularExpressionValidator* createVccValidator();

PreferencesTabs::PreferencesTabs(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DirectoryDialog)
{
    ui->setupUi(this);
    setWindowTitle("Preferences");
    ui->historySpinBox->setAlignment(Qt::AlignCenter);
    ui->okButton->setProperty("class", "dialogButton");
    ui->cancelButton->setProperty("class", "dialogButton");
    ui->defaultSettingsButton->setProperty("class", "dialogButton");
    ui->vccLineEdit->setValidator(createVccValidator());
    ui->vccLineEdit->setAlignment(Qt::AlignCenter);
    connect(ui->spiceDirToolButton, &QPushButton::clicked, this, &PreferencesTabs::onSpiceDirToolButtonClicked);
    connect(ui->libreDirToolButton, &QPushButton::clicked, this, &PreferencesTabs::onLibreDirToolButtonClicked);
    connect(ui->subcircuitDirToolButton, &QPushButton::clicked, this, &PreferencesTabs::onSubcircuitDirToolButtonClicked);
    connect(ui->okButton, &QPushButton::clicked, this, &PreferencesTabs::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &PreferencesTabs::onCancelButtonClicked);
    connect(ui->defaultSettingsButton, &QPushButton::clicked, this, &PreferencesTabs::onDefaultSettingsClicked);
    connect(ui->includeHeaderCheckbox, &QCheckBox::stateChanged, this, &PreferencesTabs::onIncludeHeaderStateChanged);
    connect(ui->josimToolButton, &QPushButton::clicked, this, &PreferencesTabs::onJosimToolButtonClicked);
    connect(ui->jsimToolButton, &QPushButton::clicked, this, &PreferencesTabs::onJsimToolButtonClicked);
    init();
}

const QRegularExpressionValidator *createVccValidator()
{
    const QString regex = R"(\d*\.{0,1}\d*([pnumkx]|meg))";
    const QRegularExpressionValidator* validator = new QRegularExpressionValidator(QRegularExpression(regex));
    return validator;
}

PreferencesTabs::~PreferencesTabs()
{
    delete ui;
}

void PreferencesTabs::apply()
{
    AppSettings::setIncludeHeader(ui->includeHeaderCheckbox->isChecked());
    AppSettings::setHeaderPattern(ui->headerPattern->text());
    AppSettings::setHistorySize(ui->historySpinBox->value());
    AppSettings::setVCCValue(ui->vccLineEdit->text());
    AppSettings::setSpiceDir(ui->spiceDirLineEdit->text());
    AppSettings::setLibreDir(ui->libreDirLineEdit->text());
    AppSettings::setSubcircuitDir(ui->subcircuitDirLineEdit->text());
    AppSettings::setJosimExecutablePath(ui->josimPath->text());
    AppSettings::setJsimExecutablePath(ui->jsimPath->text());
    AppSettings::saveSettings();
}

void PreferencesTabs::close()
{
    QWidget::close();
}

void PreferencesTabs::notifyRestartRequired()
{
    bool restartRequired = false;
    if (ui->historySpinBox->value() != AppSettings::getHistorySize()) {
        restartRequired = true;
    }
    if (restartRequired) {
        NotificationManager::showInfo(CHANGES_MESSAGE, "Restart required");
    }
}

void PreferencesTabs::onSpiceDirToolButtonClicked()
{
    QString path = ui->spiceDirLineEdit->text();
    QString newPath = FileManager::getPath(this, path);
    ui->spiceDirLineEdit->setText(newPath);
}

void PreferencesTabs::onLibreDirToolButtonClicked()
{
    QString path = ui->libreDirLineEdit->text();
    QString newPath = FileManager::getPath(this, path);
    ui->libreDirLineEdit->setText(newPath);
}

void PreferencesTabs::onSubcircuitDirToolButtonClicked() {
    QString path = ui->subcircuitDirLineEdit->text();
    QString newPath = FileManager::getPath(this, path);
    ui->subcircuitDirLineEdit->setText(newPath);
}

void PreferencesTabs::onJsimToolButtonClicked() {
    QString path = ui->jsimPath->text();
    QString newPath = FileManager::getFile(this, path);
    ui->jsimPath->setText(newPath);
}

void PreferencesTabs::onJosimToolButtonClicked()
{
    QString path = ui->josimPath->text();
    QString newPath = FileManager::getFile(this, path);
    ui->josimPath->setText(newPath);
}

void PreferencesTabs::onOkButtonClicked()
{
    notifyRestartRequired();
    apply();
    close();
}

void PreferencesTabs::onCancelButtonClicked()
{
    close();
}

void PreferencesTabs::onDefaultSettingsClicked()
{
    AppSettings::defaultSettings();
    init();
}

void PreferencesTabs::onIncludeHeaderStateChanged(int state)
{
    ui->headerPattern->setEnabled(state);
}

void PreferencesTabs::init()
{
    ui->spiceDirLineEdit->setText(AppSettings::getSpiceDir());
    ui->libreDirLineEdit->setText(AppSettings::getLibreDir());
    ui->subcircuitDirLineEdit->setText(AppSettings::getSubcircuitDir());
    ui->includeHeaderCheckbox->setChecked(AppSettings::includeHeader());
    ui->headerPattern->setText(AppSettings::getHeaderPattern());
    ui->historySpinBox->setValue(AppSettings::getHistorySize());
    ui->josimPath->setText(AppSettings::getJosimExecutablePath());
    ui->jsimPath->setText(AppSettings::getJsimExecutablePath());
    ui->headerPattern->setEnabled(AppSettings::includeHeader());
    ui->vccLineEdit->setText(AppSettings::getVCCValue());
}
