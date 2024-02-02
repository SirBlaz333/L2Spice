#ifndef PREFERENCESTABS_H
#define PREFERENCESTABS_H

#include <QTabWidget>

namespace Ui {
class PreferencesTabs;
}

class PreferencesTabs : public QTabWidget
{
    Q_OBJECT

public:
    explicit PreferencesTabs(QWidget *parent = nullptr);
    ~PreferencesTabs();

private:
    Ui::PreferencesTabs *ui;
};

#endif // PREFERENCESTABS_H
