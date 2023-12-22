#include "appsettings.h"

const QString AppSettings::libreDir = "DefaultLibreDir";
const QString AppSettings::spiceDir = "DefaultSpiceDir";
const QString AppSettings::subcircuitDir = "DefaultSubcircuitDir";
QSettings AppSettings::settings = QSettings("USMB", "L2Spice");

QString AppSettings::getSpiceDir()
{
    return settings.value(spiceDir).toString();
}

QString AppSettings::getLibreDir()
{
    return settings.value(libreDir).toString();
}

QString AppSettings::getSubcircuitDir()
{
    return settings.value(subcircuitDir).toString();
}

void AppSettings::setSpiceDir(QString dir)
{
    settings.setValue(spiceDir, dir);
}

void AppSettings::setLibreDir(QString dir)
{

    settings.setValue(libreDir, dir);
}

void AppSettings::setSubcircuitDir(QString dir)
{
    settings.setValue(subcircuitDir, dir);
}

AppSettings::AppSettings() {}

AppSettings::~AppSettings() {}
