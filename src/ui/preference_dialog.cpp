#include "preference_dialog.h"
#include "ui_directorydialog.h"

#include <QFileDialog>
#include <QSettings>

#include <src/app/app_settings.h>
#include <src/file/file_manager.h>

QString loadDirectory(QString name);

DirectoryDialog::DirectoryDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DirectoryDialog)
{
    ui->setupUi(this);
    setWindowTitle("Default directories");
    ui->spiceDirLineEdit->setText(AppSettings::getSpiceDir());
    ui->libreDirLineEdit->setText(AppSettings::getLibreDir());
    ui->subcircuitDirLineEdit->setText(AppSettings::getSubcircuitDir());
    ui->okButton->setProperty("class", "dialogButton");
    ui->cancelButton->setProperty("class", "dialogButton");
    connect(ui->spiceDirToolButton, &QPushButton::clicked, this, &DirectoryDialog::onSpiceDirToolButtonClicked);
    connect(ui->libreDirToolButton, &QPushButton::clicked, this, &DirectoryDialog::onLibreDirToolButtonClicked);
    connect(ui->subcircuitDirToolButton, &QPushButton::clicked, this, &DirectoryDialog::onSubcircuitDirToolButtonClicked);
    connect(ui->okButton, &QPushButton::clicked, this, &DirectoryDialog::onOkButtonClicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &DirectoryDialog::onCancelButtonClicked);
}

DirectoryDialog::~DirectoryDialog()
{
    delete ui;
}

void DirectoryDialog::apply()
{
    AppSettings::setSpiceDir(ui->spiceDirLineEdit->text());
    AppSettings::setLibreDir(ui->libreDirLineEdit->text());
    AppSettings::setSubcircuitDir(ui->subcircuitDirLineEdit->text());
}

void DirectoryDialog::close()
{
    QWidget::close();
}

void DirectoryDialog::onSpiceDirToolButtonClicked()
{
    QString path = ui->spiceDirLineEdit->text();
    QString newPath = FileManager::getPath(this, path);
    ui->spiceDirLineEdit->setText(newPath);
}

void DirectoryDialog::onLibreDirToolButtonClicked()
{
    QString path = ui->libreDirLineEdit->text();
    QString newPath = FileManager::getPath(this, path);
    ui->libreDirLineEdit->setText(newPath);
}

void DirectoryDialog::onSubcircuitDirToolButtonClicked() {
    QString path = ui->subcircuitDirLineEdit->text();
    QString newPath = FileManager::getPath(this, path);
    ui->subcircuitDirLineEdit->setText(newPath);
}

void DirectoryDialog::onOkButtonClicked()
{
    apply();
    close();
}

void DirectoryDialog::onCancelButtonClicked()
{
    close();
}

