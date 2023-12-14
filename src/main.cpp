#include "src/app/appsettings.h"
#include "src/ui/mainwindow.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QSettings>

QString initStyles();
void initSettings();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    a.setStyleSheet(initStyles());
    initSettings();
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

void initSettings()
{
    QDir dir;
    QString path = AppSettings::getSubcircuitDir();
    dir.setPath(path);
    if (dir.exists()) {
        return;
    }
    dir.setPath(QDir::currentPath() + "/subcircuit/");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    AppSettings::setSubcircuitDir(dir.absolutePath());
}
