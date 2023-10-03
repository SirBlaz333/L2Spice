#include "headers/mainwindow.h"

#include <QApplication>
#include <QFile>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile stylesheet(":styles/stylesheet.qss");
    if (stylesheet.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString styles = stylesheet.readAll();
        a.setStyleSheet(styles);
        stylesheet.close();
    }
    MainWindow w;
    w.show();
    return a.exec();
}
