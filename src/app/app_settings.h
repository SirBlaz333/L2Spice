#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

#include <QSettings>

class AppSettings
{
public:
    static void init();
    static void defaultSettings();
    static bool includeHeader();
    static int getHistorySize();
    static QString getHeaderPattern();
    static QString getSpiceDir();
    static QString getLibreDir();
    static QString getSubcircuitDir();
    static QString getJosimExecutablePath();
    static QString getJsimExecutablePath();
    static void setIncludeHeader(bool include);
    static void setHistorySize(int size);
    static void setHeaderPattern(QString headerPattern);
    static void setSpiceDir(QString dir);
    static void setLibreDir(QString dir);
    static void setSubcircuitDir(QString dir);
    static void setJosimExecutablePath(QString path);
    static void setJsimExecutablePath(QString path);
};

#endif // APP_SETTINGS_H
