#include "conversionparams.h"

bool ConversionParams::getSubcircuitStatus() const
{
    return subcircuitStatus;
}

QString ConversionParams::getSubcircuitName() const
{
    if (subcircuitName.isEmpty()) {
        return UNNAMED;
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

int ConversionParams::getConvertorVersion() const
{
    return convertorVersion;
}

ConversionParams::ConversionParams(bool subcircuitStatus,
                                   const QString &subcircuitName,
                                   bool fileOutput,
                                   bool consoleOutput,
                                   int convertorVersion)
    : subcircuitStatus(subcircuitStatus)
    , subcircuitName(subcircuitName)
    , fileOutput(fileOutput)
    , consoleOutput(consoleOutput)
    , convertorVersion(convertorVersion)
{}
