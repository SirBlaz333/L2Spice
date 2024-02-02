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
    ui->spiceDirLineEdit->setText(AppSettings::getSpiceDir());
    ui->libreDirLineEdit->setText(AppSettings::getLibreDir());
    ui->subcircuitDirLineEdit->setText(AppSettings::getSubcircuitDir());
    ui->okButton->setProperty("class", "dialogButton");
    ui->cancelButton->setProperty("class", "dialogButton");
    connect(ui->spiceDirToolButton, &QPushButton::clicked, this, &PreferencesTabs::onSpiceDirToolButtonClicked);
    connect(ui->libreDirToolButton, &QPushButton::clicked, this, &PreferencesTabs::onLibreDirToolButtonClicked);
    connect(ui->subcircuitDirToolButton, &QPushButton::clicked, this, &PreferencesTabs::onSubcircuitDirToolButtonClicked);
    connect(ui->okButton, &QPushButton::clicked, this, &PreferencesTabs::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &PreferencesTabs::onCancelButtonClicked);
}

PreferencesTabs::~PreferencesTabs()
{
    delete ui;
}

void PreferencesTabs::apply()
{
    AppSettings::setSpiceDir(ui->spiceDirLineEdit->text());
    AppSettings::setLibreDir(ui->libreDirLineEdit->text());
    AppSettings::setSubcircuitDir(ui->subcircuitDirLineEdit->text());
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

void PreferencesTabs::onOkButtonClicked()
{
    apply();
    close();
}

void PreferencesTabs::onCancelButtonClicked()
{
    close();
}

