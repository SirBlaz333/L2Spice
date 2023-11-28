#include "homedirectorydialog.h"
#include "ui_homedirectorydialog.h"

#include <QFileDialog>
#include <QSettings>

HomeDirectoryDialog::HomeDirectoryDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::HomeDirectoryDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setText(QSettings("USMB", "NetlistConverter").value("HomeDirectory").toString());
    setWindowTitle("Home Directory");
}

HomeDirectoryDialog::~HomeDirectoryDialog()
{
    delete ui;
}

void HomeDirectoryDialog::on_toolButton_clicked()
{
    QString path = ui->lineEdit->text();
    path = QDir(path).exists() ? path : QDir::currentPath();
    QString directory = QFileDialog::getExistingDirectory(this, "Select directory", path, QFileDialog::ShowDirsOnly);
    if (!directory.isEmpty()) {
        ui->lineEdit->setText(directory);
    }
}


void HomeDirectoryDialog::on_buttonBox_accepted()
{
    QSettings settings("USMB", "NetlistConverter");
    settings.setValue("HomeDirectory", ui->lineEdit->text());
    this->close();
}


void HomeDirectoryDialog::on_buttonBox_rejected()
{
    this->close();
}

