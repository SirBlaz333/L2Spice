#include "libre_netlist_updater.h"
#include "src/utils/attribute_utils.h"
#include "src/utils/regex_utils.h"
#include "src/utils/global_variables.h"
#include <QList>
#include <QMap>
#include <QRegularExpression>
#include <functional>
#include <regex>

const QString EMPTY_STRING = "";
const QString DEFAULT_UNIT = "none";

LibreNetlistUpdater::LibreNetlistUpdater() {}

LibreNetlistUpdater::~LibreNetlistUpdater() {}

void LibreNetlistUpdater::setSimulatorVersion(int version)
{
    simulatorVersion = version;
}

QList<QString> split(QString::iterator iterator,
                     QString::iterator end,
                     std::function<bool(QChar)> test)
{
    QList<QString> list;
    QString result;
    while (iterator != end) {
        if (test(*iterator) && !result.isEmpty()) {
            list.push_back(result);
            result = EMPTY_STRING;
        } else {
            result += *iterator;
        }
        iterator++;
    }
    if (!result.isEmpty()) {
        list.push_back(result);
    }
    return list;
}

QList<QString> splitRows(QString::iterator iterator, QString::iterator end)
{
    return split(iterator, end, [](QChar c) { return c == '\n'; });
}

QList<QString> splitParams(QString::iterator iterator, QString::iterator end){
    return split(iterator, end, [](QChar c) { return c == ' ' || c == '(' || c == ')'; });
}

QList<QString> findAllMatches(QRegularExpression regex, QString text)
{
    QRegularExpressionMatchIterator it = regex.globalMatch(text);
    QList<QString> list;
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        list.append(match.captured(0));
    }
    return list;
}

QString getAttribute(QList<QString> attributes, QString desiredName)
{
    for (QString &attribute : attributes) {
        QRegularExpressionMatch match = RegexUtils::attributeRegex.match(attribute);
        if (match.captured(1) == desiredName) {
            return match.captured(0);
        }
    }
    if (!attributes.isEmpty()) {
        return attributes.first();
    }
    return EMPTY_STRING;
}

std::string findTextByPattern(const std::string &text, const std::string &pattern)
{
    std::regex regexPattern(pattern);
    std::smatch match;
    if (std::regex_search(text, match, regexPattern)) {
        return match.str();
    }
    return EMPTY_STRING.toStdString();
}

QString getSubString(QRegularExpression regex, QString input, int captureGroup) {
    return regex.match(input).captured(captureGroup);
}

QString LibreNetlistUpdater::getNewUnit(QString param, QString attribute)
{
    QString unit = getSubString(RegexUtils::attributeRegex, attribute, 3);
    if (unit == DEFAULT_UNIT) {
        return unit;
    }
    QString unitPrefixSymbol = getSubString(RegexUtils::paramRegex, param, 2);
    QString unitFullPrefix = attributeUtils::getFullUnitPrefix(unitPrefixSymbol);
    QString unitWithoutPrefix = attributeUtils::getUnitWithoutPrefix(unit);
    return unitFullPrefix + unitWithoutPrefix;
}

QString LibreNetlistUpdater::getNewAttribute(QString attribute, QString value, QString unit)
{
    QRegularExpressionMatch match = RegexUtils::attributeRegex.match(attribute);
    QStringList capturedText = match.capturedTexts();
    attribute.replace(capturedText.at(2), QString("(unit %1)").arg(unit));
    attribute.replace(capturedText.at(4), QString("(value \"%1\")").arg(value));
    return attribute;
}

QMap<QString, QString> LibreNetlistUpdater::getComponents(QString textToUpdate)
{
    QMap<QString, QString> map;
    QRegularExpressionMatchIterator it = RegexUtils::componentRegex.globalMatch(textToUpdate);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString result = match.captured(0);
        QString name = getSubString(RegexUtils::nameRegex, result, 1);
        map[name] = result;
    }

    return map;
}

QString LibreNetlistUpdater::updateAttribute(QString textToUpdate,
                                             QString *component,
                                             QString param,
                                             QString attribute)
{
    QString unit = getNewUnit(param, attribute);
    int group = unit == DEFAULT_UNIT ? 0 : 1;
    QString value = getSubString(RegexUtils::paramRegex, param, group);
    QString newAttribute = getNewAttribute(attribute, value, unit);
    QString oldComponent = *component;
    component->replace(attribute, newAttribute);
    return textToUpdate.replace(oldComponent, *component);
}

QString getLibrePCBName(QString name)
{
    QRegularExpressionMatch match = RegexUtils::jjSpiceNameRegex.match(name);
    if (match.hasMatch()) {
        return "JJ" + match.captured(1);
    }
    return name;
}

bool isValidAttribute(int simulatorVersion, QString attribute)
{
    return (simulatorVersion == GlobalVariables::SIMULATOR_VERSION_JSIM
            && GlobalVariables::JSIM_MODEL_ATTRIBUTES.contains(attribute))
           || (simulatorVersion == GlobalVariables::SIMULATOR_VERSION_JOSIM
               && GlobalVariables::JOSIM_MODEL_ATTRIBUTES.contains(attribute));
}

QString LibreNetlistUpdater::update(QString textToUpdate,
                                    QString params,
                                    QMap<QString, QString> componentsMap)
{
    QList<QString> paramList = splitParams(params.begin(), params.end());
    //return base text if it starts with "." and not a model
    //remove the parameter if it is ".MODEL"
    QRegularExpressionMatch match = RegexUtils::specialDeclaration.match(paramList.first());
    if (match.hasMatch()) {
        if (match.captured(1) != "MODEL") {
            return textToUpdate;
        }
        paramList.pop_front();
    }
    QString name = getLibrePCBName(paramList.first());
    //remove the name;
    paramList.pop_front();
    QString component = componentsMap[name];
    //erase signals;
    QList<QString> signalList = findAllMatches(RegexUtils::signalRegex, component);
    paramList.erase(paramList.begin(), paramList.begin() + signalList.size());
    //check if the first character in first attribute is a number or not
    //if it is not, that it is a source type and we don't need to modify it for now
    if (!paramList.isEmpty() && RegexUtils::sourceTypesRegex.match(paramList.first()).hasMatch()) {
        paramList.pop_front();
    }
    QList<QString> attributes = findAllMatches(RegexUtils::attributeRegex, component);
    for (int i = 0; i < paramList.size(); i++) {
        QString param = paramList[i];
        QRegularExpressionMatch match = RegexUtils::paramWithName.match(param);
        QString value = match.hasMatch() ? match.captured(2) : param;
        QString attribute = getAttribute(attributes, match.captured(1));
        if(!attribute.isEmpty()) {
            textToUpdate = updateAttribute(textToUpdate, &component, value, attribute);
            attributes.removeOne(attribute);
        }
    }
    for (QString &attribute : attributes) {
        if(isValidAttribute(simulatorVersion, attribute)) {
            textToUpdate = updateAttribute(textToUpdate, &component, EMPTY_STRING, attribute);
        }
    }

    return textToUpdate;
}

QString LibreNetlistUpdater::removeSubcircuitImports(QString param)
{
    QRegularExpressionMatchIterator it = RegexUtils::subcircuitRegex.globalMatch(param);
    if (it.hasNext() && it.next().captured(0) == param) {
        return param;
    }
    while (it.hasNext()) {
        param.replace(it.next().captured(0), EMPTY_STRING);
    }
    return param;
}

bool canUpdate(QString row) {
    return !RegexUtils::comment.match(row).hasMatch()
           && !row.startsWith("VCC")
           && !row.startsWith("X");
}

QString LibreNetlistUpdater::updateNetlist(QString textToUpdate, QString newParams)
{
    newParams = removeSubcircuitImports(newParams);
    QList<QString> rows = splitRows(newParams.begin(), newParams.end());
    QMap<QString, QString> componentsMap = getComponents(textToUpdate);
    for (QString row : rows) {
        row = row.trimmed();
        if (canUpdate(row)) {
            textToUpdate = update(textToUpdate, row, componentsMap);
        }
    }
    return textToUpdate;
}
