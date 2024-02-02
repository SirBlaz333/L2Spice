#ifndef PREFERENCES_TABS_H
#define PREFERENCES_TABS_H

#include <QDialog>

namespace Ui {
class DirectoryDialog;
}

class PreferencesTabs : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesTabs(QWidget *parent = nullptr);
    ~PreferencesTabs();

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

#endif // PREFERENCES_TABS_H
