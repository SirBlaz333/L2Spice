#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QSettings>

class AppSettings
{
public:
    static QSettings getSettings() { return QSettings("USMB", "NetlistConverter"); }
    AppSettings();
    ~AppSettings();
};

#endif // APPSETTINGS_H
