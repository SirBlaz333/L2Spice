#ifndef CONVERSION_PARAMS_H
#define CONVERSION_PARAMS_H

#include "src/utils/global_variables.h"

#include <QString>

class ConversionParams
{
private:
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
                     int simulatorVersion = SIMULATOR_VERSION_JOSIM);
    ConversionParams(const ConversionParams &params) = default;
    ConversionParams &operator=(const ConversionParams &params) = default;

    bool getSubcircuitStatus() const;
    QString getSubcircuitName() const;
    bool getFileOutput() const;
    bool getConsoleOutput() const;
    int getSimulatorVersion() const;
};

#endif // CONVERSION_PARAMS_H
