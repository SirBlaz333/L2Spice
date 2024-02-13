#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

#include <QMap>
#include <QString>

class AppSettings
{
private:
    static QMap<QString, QString> settings;
    static QMap<QString, QString> model;

public:
    static void loadSettings();
    static void saveSettings();
    static void defaultSettings();
    static bool includeHeader();
    static int getHistorySize();
    static QString getHeaderPattern();
    static QString getVCCValue();
    static QString getSpiceDir();
    static QString getLibreDir();
    static QString getSubcircuitDir();
    static QString getJosimExecutablePath();
    static QString getJsimExecutablePath();
    static void setIncludeHeader(bool include);
    static void setHistorySize(int size);
    static void setHeaderPattern(QString headerPattern);
    static void setVCCValue(QString value);
    static void setSpiceDir(QString dir);
    static void setLibreDir(QString dir);
    static void setSubcircuitDir(QString dir);
    static void setJosimExecutablePath(QString path);
    static void setJsimExecutablePath(QString path);
    static QMap<QString, QString> getDefaultModel();
};

#endif // APP_SETTINGS_H
