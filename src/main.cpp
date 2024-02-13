#include "src/app/app_settings.h"
#include "src/ui/mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QSettings>

#include <src/console/console_app.h>

QString initStyles();
void initDefaultSettings();

int main(int argc, char *argv[])
{
    if (argc > 1) {
        ConsoleApplication c(argc, argv);
        return c.exec();
    }
    QApplication a(argc, argv);
    MainWindow w;
    a.setStyleSheet(initStyles());
    initDefaultSettings();
    w.show();
    return a.exec();
}

QString initStyles()
{
    QFile stylesheet(":styles/stylesheet.qss");
    if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QString styles = stylesheet.readAll();
        stylesheet.close();
        return styles;
    }
    return "";
}

void initDefaultSettings()
{
    AppSettings::loadSettings();
}
