#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

class AppSettings
{
private:
    const static QString libreDir;
    const static QString spiceDir;
    static QSettings settings;
public:
    static QString getSpiceDir();
    static QString getLibreDir();
    static void setSpiceDir(QString dir);
    static void setLibreDir(QString dir);
    AppSettings();
    ~AppSettings();
};

#endif // APPSETTINGS_H
