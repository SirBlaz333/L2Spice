#ifndef CONVERSIONPARAMS_H
#define CONVERSIONPARAMS_H

#include <QString>

class ConversionParams
{
private:
    const QString UNNAMED = "UNNAMED";

    bool subcircuitStatus;
    QString subcircuitName;
    bool fileOutput;
    bool consoleOutput;
    int simulatorVersion;
public:
    ConversionParams(bool subcircuitStatus = false,
                     const QString &subcircuitName = QString(),
                     bool fileOutput = true,
                     bool consoleOutput = true,
                     int convertorVersion = 1);

    bool getSubcircuitStatus() const;
    QString getSubcircuitName() const;
    bool getFileOutput() const;
    bool getConsoleOutput() const;
    int getSimulatorVersion() const;
};

#endif // CONVERSIONPARAMS_H
