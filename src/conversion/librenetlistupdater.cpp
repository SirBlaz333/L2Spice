#include "librenetlistupdater.h"
#include "src/utils/attributeutils.h"
#include "src/utils/regexutils.h"
#include <QList>
#include <QMap>
#include <QRegularExpression>
#include <functional>
#include <regex>

LibreNetlistUpdater::LibreNetlistUpdater() {}

LibreNetlistUpdater::~LibreNetlistUpdater() {}

QList<QString> split(QString::iterator iterator,
                     QString::iterator end,
                     std::function<bool(QChar)> test)
{
    QList<QString> list;
    QString result;
    while (iterator != end) {
        if (test(*iterator) && !result.isEmpty()) {
            list.push_back(result);
            result = "";
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

QList<QString> findAllMatches(QRegularExpression* regex, QString text)
{
    QRegularExpressionMatchIterator it = regex->globalMatch(text);
    QList<QString> list;
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        list.append(match.captured(0));
    }
    return list;
}

std::string findTextByPattern(const std::string &text, const std::string &pattern)
{
    std::regex regexPattern(pattern);
    std::smatch match;
    if (std::regex_search(text, match, regexPattern)) {
        return match.str();
    }
    return "";
}

QString getSubString(QRegularExpression* regex, QString input, int captureGroup) {
    return regex->match(input).captured(captureGroup);
}

QString LibreNetlistUpdater::getNewUnit(QString param, QString attribute)
{
    QString unit = getSubString(RegexUtils::attributeRegex, attribute, 2);
    if (unit == "none") {
        return unit;
    }
    QString unitPrefixSymbol = getSubString(RegexUtils::paramRegex, param, 2);
    QString unitFullPrefix = attributeUtils::getFullUnitPrefix(unitPrefixSymbol);
    QString unitWithoutPrefix = attributeUtils::getUnitWithoutPrefix(unit);
    return unitFullPrefix + unitWithoutPrefix;
}

QString LibreNetlistUpdater::getNewAttribute(QString attribute, QString value, QString unit)
{
    QRegularExpressionMatch match = RegexUtils::attributeRegex->match(attribute);
    QStringList capturedText = match.capturedTexts();
    attribute.replace(capturedText.at(1), QString("(unit %1)").arg(unit));
    attribute.replace(capturedText.at(3), QString("(value \"%1\")").arg(value));
    return attribute;
}

QMap<QString, QString> LibreNetlistUpdater::getComponents(QString textToUpdate)
{
    QMap<QString, QString> map;
    QRegularExpressionMatchIterator it = RegexUtils::componentRegex->globalMatch(textToUpdate);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString result = match.captured(0);
        QString name = getSubString(RegexUtils::nameRegex, result, 1);
        map[name] = result;
    }

    return map;
}

QString LibreNetlistUpdater::updateParameter(QString textToUpdate,
                                        QString *component,
                                        QString param,
                                        QString attribute)
{
    QString unit = getNewUnit(param, attribute);
    int group = unit == "none" ? 0 : 1;
    QString value = getSubString(RegexUtils::paramRegex, param, group);
    QString newAttribute = getNewAttribute(attribute, value, unit);
    QString oldComponent = *component;
    component->replace(attribute, newAttribute);
    return textToUpdate.replace(oldComponent, *component);
}

QString LibreNetlistUpdater::update(QString textToUpdate,
                               QString params,
                               QMap<QString, QString> componentsMap)
{
    QList<QString> paramList = splitParams(params.begin(), params.end());
    QString name = paramList[0];
    //remove the name;
    paramList.pop_front();
    QString component = componentsMap[name];
    //erase signals;
    QList<QString> signalList = findAllMatches(RegexUtils::signalRegex, component);
    paramList.erase(paramList.constBegin(), paramList.constBegin() + signalList.size());
    //check if the first character in first attribute is a number or not
    //if it is not, that it is a source type and we don't need to modify it for now
    if (!paramList.isEmpty() && RegexUtils::sourceTypesRegex->match(paramList.first()).hasMatch()) {
        paramList.pop_front();
    }
    QList<QString> attributeList = findAllMatches(RegexUtils::attributeRegex, component);
    for (int i = 0; i < paramList.size(); i++) {
        textToUpdate = updateParameter(textToUpdate, &component, paramList[i], attributeList[i]);
    }
    for (int i = paramList.size(); i < attributeList.size(); i++) {
        textToUpdate = updateParameter(textToUpdate, &component, "", attributeList[i]);
    }

    return textToUpdate;
}

QString LibreNetlistUpdater::removeSubcircuitImports(QString param)
{
    QRegularExpressionMatchIterator it = RegexUtils::subcircuitRegex->globalMatch(param);
    if (it.hasNext() && it.next().captured(0) == param) {
        return param;
    }
    while (it.hasNext()) {
        param.replace(it.next().captured(0), "");
    }
    return param;
}

QString LibreNetlistUpdater::updateNetlist(QString textToUpdate, QString oldParams, QString newParams)
{
    newParams = removeSubcircuitImports(newParams);
    oldParams = removeSubcircuitImports(oldParams);
    QList<QString> oldRows = splitRows(oldParams.begin(), oldParams.end());
    QList<QString> newRows = splitRows(newParams.begin(), newParams.end());
    QMap<QString, QString> componentsMap = getComponents(textToUpdate);
    if (oldRows.size() != newRows.size()) {
        return "";
    }
    unsigned int i = 0;
    while (i < oldRows.size()) {
        QString oldRow = oldRows[i];
        QString newRow = newRows[i];
        if (oldRow != newRow) {
            textToUpdate = update(textToUpdate, newRow, componentsMap);
        }
        i++;
    }
    return textToUpdate;
}
