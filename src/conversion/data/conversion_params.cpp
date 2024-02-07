#include "conversion_params.h"

Q_GLOBAL_STATIC(QString, UNNAMED, "UNNAMED");

bool ConversionParams::getSubcircuitStatus() const
{
    return subcircuitStatus;
}

QString ConversionParams::getSubcircuitName() const
{
    if (subcircuitName.isEmpty()) {
        return *UNNAMED;
    }
    return subcircuitName;
}

bool ConversionParams::getFileOutput() const
{
    return fileOutput;
}

bool ConversionParams::getConsoleOutput() const
{
    return consoleOutput;
}

int ConversionParams::getSimulatorVersion() const
{
    return simulatorVersion;
}

ConversionParams::ConversionParams(bool subcircuitStatus,
                                   const QString &subcircuitName,
                                   bool fileOutput,
                                   bool consoleOutput,
                                   int simulatorVersion)
    : subcircuitStatus(subcircuitStatus)
    , subcircuitName(subcircuitName)
    , fileOutput(fileOutput)
    , consoleOutput(consoleOutput)
    , simulatorVersion(simulatorVersion)
{}
