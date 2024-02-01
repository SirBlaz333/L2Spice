#ifndef PREFERENCE_DIALOG_H
#define PREFERENCE_DIALOG_H

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
    void onSubcircuitDirToolButtonClicked();
    void onOkButtonClicked();
    void onCancelButtonClicked();

private:
    Ui::DirectoryDialog *ui;
    void apply();
    void close();
};

#endif // PREFERENCE_DIALOG_H
