#include "defaultdirectorydialog.h"
#include "ui_defaultdirectorydialog.h"

#include <QFileDialog>
#include <QSettings>

#include <src/app/appsettings.h>

DefaultDirectoryDialog::DefaultDirectoryDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DefaultDirectoryDialog)
{
    ui->setupUi(this);
    QString path = AppSettings::getSettings().value("DefaultDirectory").toString();
    QString currentPath = path == "" ? QDir::currentPath() : path;
    ui->lineEdit->setText(currentPath);
    setWindowTitle("Default Directory");
}

DefaultDirectoryDialog::~DefaultDirectoryDialog()
{
    delete ui;
}

void DefaultDirectoryDialog::on_toolButton_clicked()
{
    QString path = ui->lineEdit->text();
    path = QDir(path).exists() ? path : QDir::currentPath();
    QString directory = QFileDialog::getExistingDirectory(this, "Select directory", path, QFileDialog::ShowDirsOnly);
    if (!directory.isEmpty()) {
        ui->lineEdit->setText(directory);
    }
}


void DefaultDirectoryDialog::on_buttonBox_accepted()
{
    AppSettings::getSettings().setValue("DefaultDirectory", ui->lineEdit->text());
    this->close();
}


void DefaultDirectoryDialog::on_buttonBox_rejected()
{
    this->close();
}

