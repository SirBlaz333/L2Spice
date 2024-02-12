#include "app_header.h"
#include "app_settings.h"
#include "src/utils/global_variables.h"
#include "src/utils/regex_utils.h"

#include <sstream>
#include <iomanip>
#include <chrono>
#include <QString>

#include <src/conversion/data/conversion_params.h>

const QString UNKNOWN_NAME = "UNKNOWN";
const QString HEADER_LINE = "<header><b>*%1</b><header><br><br>";

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
    if (!AppSettings::includeHeader() || AppSettings::getHeaderPattern().isEmpty()) {
        return "";
    }
    QString simulator = params.getSimulatorVersion() == GlobalVariables::SIMULATOR_VERSION_JOSIM ? "JoSIM" : "JSIM";
    QString project = RegexUtils::projectPath.match(sourceFile).captured(1);
    project = project.isEmpty() ? UNKNOWN_NAME : project;
    QString headerPattern = HEADER_LINE.arg(AppSettings::getHeaderPattern());
    headerPattern.replace("%1", getTime());
    headerPattern.replace("%2", project);
    headerPattern.replace("%3", simulator);
    return headerPattern;
}

