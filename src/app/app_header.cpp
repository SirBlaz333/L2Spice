#include "app_header.h"
#include "src/utils/regex_utils.h"
#include "src/utils/global_variables.h"

#include <iomanip>
#include <chrono>
#include <QString>

#include <src/conversion/data/conversion_params.h>

Q_GLOBAL_STATIC(QString, UNKNOWN_NAME, "UNKNOWN");
Q_GLOBAL_STATIC(QString, HEADER_LINE,
                "*Converted %1 from the \"%2\" LibrePCB project by L2Spice for %3 simulator.\n\n");

AppHeader::AppHeader() {}


QString getTime()
{
    auto currentTime = std::chrono::system_clock::now();
    std::time_t currentTimeAsTimeT = std::chrono::system_clock::to_time_t(currentTime);
    std::tm *currentTimeAsTM = std::localtime(&currentTimeAsTimeT);
    std::ostringstream oss;
    oss << std::put_time(currentTimeAsTM, "%Y-%m-%d %H:%M:%S");
    return QString::fromStdString(oss.str());
}

QString AppHeader::getHeader(ConversionParams params, QString sourceFile)
{
    QString simulator = params.getSimulatorVersion() == SIMULATOR_VERSION_JOSIM ? "JoSIM" : "JSIM";
    QString project = RegexUtils::projectPath->match(sourceFile).captured(1);
    project = project.isEmpty() ? *UNKNOWN_NAME : project;
    return HEADER_LINE->arg(getTime(), project, simulator);
}

