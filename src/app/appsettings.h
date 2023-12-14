#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

class AppSettings
{
private:
    const static QString libreDir;
    const static QString spiceDir;
    const static QString subcircuitDir;
    static QSettings settings;
public:
    static QString getSpiceDir();
    static QString getLibreDir();
    static QString getSubcircuitDir();
    static void setSpiceDir(QString dir);
    static void setLibreDir(QString dir);
    static void setSubcircuitDir(QString dir);
    AppSettings();
    ~AppSettings();
};

#endif // APPSETTINGS_H
