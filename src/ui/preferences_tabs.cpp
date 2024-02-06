#include "preferences_tabs.h"
#include "ui_preferences.h"

#include <QFileDialog>
#include <QSettings>

#include <src/app/app_settings.h>
#include <src/file/file_manager.h>

QString loadDirectory(QString name);

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
    connect(ui->spiceDirToolButton, &QPushButton::clicked, this, &PreferencesTabs::onSpiceDirToolButtonClicked);
    connect(ui->libreDirToolButton, &QPushButton::clicked, this, &PreferencesTabs::onLibreDirToolButtonClicked);
    connect(ui->subcircuitDirToolButton, &QPushButton::clicked, this, &PreferencesTabs::onSubcircuitDirToolButtonClicked);
    connect(ui->okButton, &QPushButton::clicked, this, &PreferencesTabs::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &PreferencesTabs::onCancelButtonClicked);
    connect(ui->defaultSettingsButton, &QPushButton::clicked, this, &PreferencesTabs::onDefaultSettingsClicked);
    connect(ui->includeHeaderCheckbox, &QCheckBox::stateChanged, this, &PreferencesTabs::onIncludeHeaderStateChanged);
    init();
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
    AppSettings::setSpiceDir(ui->spiceDirLineEdit->text());
    AppSettings::setLibreDir(ui->libreDirLineEdit->text());
    AppSettings::setSubcircuitDir(ui->subcircuitDirLineEdit->text());
    AppSettings::setJosimExecutablePath(ui->josimPath->text());
    AppSettings::setJsimExecutablePath(ui->jsimPath->text());
}

void PreferencesTabs::close()
{
    QWidget::close();
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

void PreferencesTabs::onJosimToolButtonClicked() {
    QString path = ui->jsimPath->text();
    QString newPath = FileManager::getPath(this, path);
    ui->jsimPath->setText(newPath);
}

void PreferencesTabs::onJsimToolButtonClicked()
{
    QString path = ui->josimPath->text();
    QString newPath = FileManager::getPath(this, path);
    ui->josimPath->setText(newPath);
}

void PreferencesTabs::onOkButtonClicked()
{
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
}
