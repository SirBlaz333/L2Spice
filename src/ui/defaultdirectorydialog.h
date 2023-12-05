#ifndef DEFAULTDIRECTORYDIALOG_H
#define DEFAULTDIRECTORYDIALOG_H

#include <QDialog>

namespace Ui {
class DefaultDirectoryDialog;
}

class DefaultDirectoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DefaultDirectoryDialog(QWidget *parent = nullptr);
    ~DefaultDirectoryDialog();

private slots:
    void on_toolButton_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DefaultDirectoryDialog *ui;
};

#endif // DEFAULTDIRECTORYDIALOG_H
