#ifndef HOMEDIRECTORYDIALOG_H
#define HOMEDIRECTORYDIALOG_H

#include <QDialog>

namespace Ui {
class HomeDirectoryDialog;
}

class HomeDirectoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HomeDirectoryDialog(QWidget *parent = nullptr);
    ~HomeDirectoryDialog();

private slots:
    void on_toolButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::HomeDirectoryDialog *ui;
};

#endif // HOMEDIRECTORYDIALOG_H
