#ifndef APP_SETTINGS_H
#define APP_SETTINGS_H

#include <QMap>
#include <QString>

/**
 * AppSettings is used to have common settings within all the application.
 */
class AppSettings
{
private:
    static QMap<QString, QString> settings;
    static QList<QPair<QString, QString>> model;

public:
    /**
     * Loads the settings from the file.
     */
    static void loadSettings();

    /**
     * Saves the settings to the file.
     */
    static void saveSettings();

    /**
     * Reset some settings to their default values.
     */
    static void defaultSettings();

    /**
     * @return whether the header included for the conversion or not.
     */
    static bool includeHeader();

    /**
     * @return the size of the history storage.
     */
    static int getHistorySize();

    /**
     * @return the header pattern for the conversion.
     */
    static QString getHeaderPattern();

    /**
     * @return the VCC voltage value for the conversion.
     */
    static QString getVCCValue();

    /**
     * @return the directory which is used to open/save files for SPICE netlists.
     */
    static QString getSpiceDir();

    /**
     * @return the directory which is used to open/save files for LibrePCB circuits.
     */
    static QString getLibreDir();

    /**
     * @return the directory which is used to open/save files for SPICE subcircuits.
     */
    static QString getSubcircuitDir();

    /**
     * @return the path to JoSIM simulator executable.
     */
    static QString getJosimExecutablePath();

    /**
     * @return the path to JSIM simulator executable.
     */
    static QString getJsimExecutablePath();

    /**
     * @return list of pairs that contains default model parameters.
     */
    static QList<QPair<QString, QString>> getDefaultModel();

    /**
     * Sets new value to the "include header" parameter.
     * @param include - whether the header is included or not.
     */
    static void setIncludeHeader(bool include);

    /**
     * Sets new history storage size.
     * @param size - new size of the storage.
     */
    static void setHistorySize(int size);

    /**
     * Sets new header pattern.
     * @param headerPattern - new header pattern.
     */
    static void setHeaderPattern(QString headerPattern);

    /**
     * Sets new VCC voltage.
     * @param voltage - new VCC voltage.
     */
    static void setVCCValue(QString voltage);

    /**
     * Sets new SPICE directory. It will be used to open/save files for SPICE netlits.
     * @param dir - new SPICE directory.
     */
    static void setSpiceDir(QString dir);

    /**
     * Sets new LibrePCB directory. It will be used to open/save files for LibrePCB circuits.
     * @param dir - new LibrePCB directory.
     */
    static void setLibreDir(QString dir);

    /**
     * Sets new subcircuit directory. It will be used to open/save files for SPICE subcircuits.
     * @param dir - new subcircuit directory.
     */
    static void setSubcircuitDir(QString dir);

    /**
     * Sets new path to JoSIM executable.
     * @param dir - new JoSIM executalb path.
     */
    static void setJosimExecutablePath(QString path);

    /**
     * Sets new path to JSIM executable.
     * @param dir - new JSIM executalb path.
     */
    static void setJsimExecutablePath(QString path);
};

#endif // APP_SETTINGS_H
