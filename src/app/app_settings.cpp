#include "app_settings.h"

#include <qdir.h>

const QString HEADER = "header";
const QString HISTORY_SIZE = "historySize";
const int DEFAULT_HISTORY_SIZE = 10;
const QString HEADER_PATTERN = "headerPattern";
const QString DEFAULT_HEADER_PATTERN = "Converted %1 from the \"%2\" LibrePCB project by L2Spice for %3 simulator.";
const QString JOSIM_PATH = "josimPath";
const QString JSIM_PATH = "jsimPath";
const QString LIBRE_DIR = "libreDir";
const QString SPICE_DIR = "spiceDir";
const QString SUBCIRCUIT_DIR = "subcircuitDir";
QSettings AppSettings::settings = QSettings("USMB", "L2Spice");

QString initSubcircuitDir()
{
    QDir dir(QDir::currentPath() + "/subcircuit/");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return dir.absolutePath();
}

void AppSettings::init()
{
    QDir dir(getSubcircuitDir());
    if (!dir.exists()) {
        setSubcircuitDir(initSubcircuitDir());
    }
    if (getHeaderPattern().isEmpty()) {
        setHeaderPattern(DEFAULT_HEADER_PATTERN);
    }
    if (getHistorySize() == 0) {
        setHistorySize(DEFAULT_HISTORY_SIZE);
    }
}

void AppSettings::defaultSettings()
{
    AppSettings::setHistorySize(DEFAULT_HISTORY_SIZE);
    AppSettings::setIncludeHeader(true);
    AppSettings::setSpiceDir("");
    AppSettings::setLibreDir("");
    AppSettings::setSubcircuitDir(initSubcircuitDir());
    AppSettings::setJosimExecutablePath("");
    AppSettings::setJsimExecutablePath("");
    AppSettings::setHeaderPattern("");
    AppSettings::init();
}

bool AppSettings::includeHeader()
{
    return settings.value(HEADER).toBool();
}

int AppSettings::getHistorySize()
{
    return settings.value(HISTORY_SIZE).toInt();
}

QString AppSettings::getHeaderPattern()
{
    return settings.value(HEADER_PATTERN).toString();
}

QString AppSettings::getSpiceDir()
{
    return settings.value(SPICE_DIR).toString();
}

QString AppSettings::getLibreDir()
{
    return settings.value(LIBRE_DIR).toString();
}

QString AppSettings::getSubcircuitDir()
{
    return settings.value(SUBCIRCUIT_DIR).toString();
}

QString AppSettings::getJosimExecutablePath()
{
    return settings.value(JOSIM_PATH).toString();
}

QString AppSettings::getJsimExecutablePath()
{
    return settings.value(JSIM_PATH).toString();
}

void AppSettings::setIncludeHeader(bool include)
{
    settings.setValue(HEADER, include);
}

void AppSettings::setHistorySize(int size)
{
    settings.setValue(HISTORY_SIZE, size);
}

void AppSettings::setHeaderPattern(QString headerPattern)
{
    settings.setValue(HEADER_PATTERN, headerPattern);
}

void AppSettings::setSpiceDir(QString dir)
{
    settings.setValue(SPICE_DIR, dir);
}

void AppSettings::setLibreDir(QString dir)
{

    settings.setValue(LIBRE_DIR, dir);
}

void AppSettings::setSubcircuitDir(QString dir)
{
    settings.setValue(SUBCIRCUIT_DIR, dir);
}

void AppSettings::setJosimExecutablePath(QString path)
{
    settings.setValue(JOSIM_PATH, path);
}

void AppSettings::setJsimExecutablePath(QString path)
{
    settings.setValue(JSIM_PATH, path);
}
