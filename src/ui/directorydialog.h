#ifndef DIRECTORYDIALOG_H
#define DIRECTORYDIALOG_H

#include <QDialog>

namespace Ui {
class DirectoryDialog;
}

class DirectoryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DirectoryDialog(QWidget *parent = nullptr);
    ~DirectoryDialog();

private slots:
    void onSpiceDirToolButtonClicked();
    void onLibreDirToolButtonClicked();
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::DirectoryDialog *ui;
    void apply();
    void close();
};

#endif // DIRECTORYDIALOG_H
