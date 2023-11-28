#include "src/ui/mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QSettings>

QString initStyles();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyleSheet(initStyles());
    MainWindow w;
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
