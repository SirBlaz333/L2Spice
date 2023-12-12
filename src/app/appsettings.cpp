#include "appsettings.h"

const QString AppSettings::libreDir = "DefaultLibreDir";
const QString AppSettings::spiceDir = "DefaultSpiceDir";
QSettings AppSettings::settings = QSettings("USMB", "NetlistConverter");

QString AppSettings::getSpiceDir()
{
    return settings.value(spiceDir).toString();
}

QString AppSettings::getLibreDir()
{
    return settings.value(libreDir).toString();
}

void AppSettings::setSpiceDir(QString dir)
{
    settings.setValue(spiceDir, dir);
}

void AppSettings::setLibreDir(QString dir)
{

    settings.setValue(libreDir, dir);
}

AppSettings::AppSettings() {}

AppSettings::~AppSettings() {}
