#include "app_settings.h"
#include "src/utils/regex_utils.h"
#include <src/file/file_manager.h>

#include <qdir.h>

const QString HEADER = "INCLUDE_HEADER";
const QString HISTORY_SIZE = "HISTORY_SIZE";
const int DEFAULT_HISTORY_SIZE = 10;
const QString HEADER_PATTERN = "HEADER_PATTERN";
const QString VCC = "VCC";
const QString DEFAULT_HEADER_PATTERN = "Converted %1 from the \"%2\" LibrePCB project by L2Spice for %3 simulator.";
const QString JOSIM_PATH = "JOSIM_PATH";
const QString JSIM_PATH = "JSIM_PATH";
const QString LIBRE_DIR = "LIBRE_DIR";
const QString SPICE_DIR = "SPICE_DIR";
const QString SUBCIRCUIT_DIR = "SUBCIRCUIT_DIR";

QMap<QString, QString> AppSettings::settings = QMap<QString, QString>();
QMap<QString, QString> AppSettings::model = QMap<QString, QString>();

QString initSubcircuitDir()
{
    QDir dir(QDir::currentPath() + "/subcircuit/");
    if (!dir.exists()) {
        dir.mkpath(".");
    }
    return dir.absolutePath();
}

void AppSettings::loadSettings()
{
    QString fileSettings = FileManager::loadFile(QDir::currentPath() + "/settings/settings.txt");
    QRegularExpressionMatchIterator it = RegexUtils::settingRegex.globalMatch(fileSettings);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        settings.insert(match.captured(1), match.captured(2));
    }

    QString fileModel = FileManager::loadFile(QDir::currentPath() + "/settings/model.txt");
    it = RegexUtils::settingRegex.globalMatch(fileModel);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        model.insert(match.captured(1), match.captured(2));
    }

    QDir dir(getSubcircuitDir());
    if (!dir.exists()) {
        setSubcircuitDir(initSubcircuitDir());
    }
}

void AppSettings::saveSettings()
{
    QString data;
    for (QString key : settings.keys()) {
        data += key + "=" + settings[key] + "\n";
    }
    FileManager::save(QDir::currentPath() + "/settings/settings.txt", data);
}

void AppSettings::defaultSettings()
{
    AppSettings::setHistorySize(DEFAULT_HISTORY_SIZE);
    AppSettings::setIncludeHeader(true);
    AppSettings::setHeaderPattern(DEFAULT_HEADER_PATTERN);
    AppSettings::setVCCValue("2.5m");
    AppSettings::setSubcircuitDir(initSubcircuitDir());
}

bool AppSettings::includeHeader()
{
    return settings.value(HEADER).toInt();
}

int AppSettings::getHistorySize()
{
    return settings.value(HISTORY_SIZE).toInt();
}

QString AppSettings::getVCCValue()
{
    return settings.value(VCC);
}

QString AppSettings::getHeaderPattern()
{
    return settings.value(HEADER_PATTERN);
}

QString AppSettings::getSpiceDir()
{
    return settings.value(SPICE_DIR);
}

QString AppSettings::getLibreDir()
{
    return settings.value(LIBRE_DIR);
}

QString AppSettings::getSubcircuitDir()
{
    return settings.value(SUBCIRCUIT_DIR);
}

QString AppSettings::getJosimExecutablePath()
{
    return settings.value(JOSIM_PATH);
}

QString AppSettings::getJsimExecutablePath()
{
    return settings.value(JSIM_PATH);
}

void AppSettings::setIncludeHeader(bool include)
{
    settings.insert(HEADER, QString::number(include));
}

void AppSettings::setHistorySize(int size)
{
    settings.insert(HISTORY_SIZE, QString::number(size));
}

void AppSettings::setHeaderPattern(QString headerPattern)
{
    settings.insert(HEADER_PATTERN, headerPattern);
}

void AppSettings::setVCCValue(QString value)
{
    settings.insert(VCC, value);
}

void AppSettings::setSpiceDir(QString dir)
{
    settings.insert(SPICE_DIR, dir);
}

void AppSettings::setLibreDir(QString dir)
{

    settings.insert(LIBRE_DIR, dir);
}

void AppSettings::setSubcircuitDir(QString dir)
{
    settings.insert(SUBCIRCUIT_DIR, dir);
}

void AppSettings::setJosimExecutablePath(QString path)
{
    settings.insert(JOSIM_PATH, path);
}

void AppSettings::setJsimExecutablePath(QString path)
{
    settings.insert(JSIM_PATH, path);
}

QMap<QString, QString> AppSettings::getDefaultModel()
{
    return model;
}
