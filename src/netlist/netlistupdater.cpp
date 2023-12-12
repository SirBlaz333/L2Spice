#include "netlistupdater.h"
#include "src/utils/attributeutils.h"
#include <QList>
#include <QMap>
#include <QRegularExpression>
#include <functional>
#include <regex>

const QRegularExpression NetlistUpdater::componentRegex = QRegularExpression(
    R"(\(component.+?\n\s\))", QRegularExpression::DotMatchesEverythingOption);
const QRegularExpression NetlistUpdater::nameRegex = QRegularExpression(R"(\(name \"(.+?)\"\))");
const QRegularExpression NetlistUpdater::paramRegex = QRegularExpression(R"((\d*)(\w*))");
const QRegularExpression NetlistUpdater::attributeRegex = QRegularExpression(
    R"(\(attribute \"\w+\" \(type \w+\) (\(unit (\w+)\)) (\(value \"([\d\w]*)\"\))\))");
const QRegularExpression NetlistUpdater::signalRegex = QRegularExpression(
    R"(\(signal .+? \(net .+?\)\))");
const QRegularExpression NetlistUpdater::sourceTypesRegex
    = QRegularExpression(R"(DC|PWL|PULSE|SIN|CUS|NOISE|EXP)",
                         QRegularExpression::CaseInsensitiveOption);
const QRegularExpression NetlistUpdater::subcircuitRegex
    = QRegularExpression(R"(\.SUBCKT.+?\.ENDS\n)", QRegularExpression::DotMatchesEverythingOption);

NetlistUpdater::NetlistUpdater() {}

NetlistUpdater::~NetlistUpdater() {}

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

std::string findTextByPattern(const std::string &text, const std::string &pattern)
{
    std::regex regexPattern(pattern);
    std::smatch match;
    if (std::regex_search(text, match, regexPattern)) {
        return match.str();
    }
    return "";
}

QString getSubString(QRegularExpression regex, QString input, int captureGroup) {
    return regex.match(input).captured(captureGroup);
}

QString NetlistUpdater::getNewUnit(QString param, QString attribute)
{
    QString unit = getSubString(attributeRegex, attribute, 2);
    if (unit == "none") {
        return unit;
    }
    QString unitPrefixSymbol = getSubString(paramRegex, param, 2);
    QString unitFullPrefix = attribute_utils::getFullUnitPrefix(unitPrefixSymbol);
    QString unitWithoutPrefix = attribute_utils::getUnitWithoutPrefix(unit);
    return unitFullPrefix + unitWithoutPrefix;
}

QString NetlistUpdater::getNewAttribute(QString attribute, QString value, QString unit)
{
    QRegularExpressionMatch match = attributeRegex.match(attribute);
    QStringList capturedText = match.capturedTexts();
    attribute.replace(capturedText.at(1), QString("(unit %1)").arg(unit));
    attribute.replace(capturedText.at(3), QString("(value \"%1\")").arg(value));
    return attribute;
}

QMap<QString, QString> NetlistUpdater::getComponents(QString textToUpdate)
{
    QMap<QString, QString> map;
    QRegularExpressionMatchIterator it = componentRegex.globalMatch(textToUpdate);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString result = match.captured(0);
        QString name = getSubString(nameRegex, result, 1);
        map[name] = result;
    }

    return map;
}

QString NetlistUpdater::updateParameter(QString textToUpdate,
                                        QString *component,
                                        QString param,
                                        QString attribute)
{
    QString unit = getNewUnit(param, attribute);
    int group = unit == "none" ? 0 : 1;
    QString value = getSubString(paramRegex, param, group);
    QString newAttribute = getNewAttribute(attribute, value, unit);
    QString oldComponent = *component;
    component->replace(attribute, newAttribute);
    return textToUpdate.replace(oldComponent, *component);
}

QString NetlistUpdater::update(QString textToUpdate,
                               QString params,
                               QMap<QString, QString> componentsMap)
{
    QList<QString> paramList = splitParams(params.begin(), params.end());
    QString name = paramList[0];
    //remove the name;
    paramList.pop_front();
    QString component = componentsMap[name];
    //erase signals;
    QList<QString> signalList = findAllMatches(signalRegex, component);
    paramList.erase(paramList.begin(), paramList.begin() + signalList.size());
    //check if there are parameters left;
    if (paramList.empty()) {
        return textToUpdate;
    }
    //check if the first character in first attribute is a number or not
    //if it is not, that it is a source type and we don't need to modify it for now
    if (sourceTypesRegex.match(paramList.first()).hasMatch()) {
        paramList.pop_front();
    }
    QList<QString> attributeList = findAllMatches(attributeRegex, component);
    for (int i = 0; i < paramList.size(); i++) {
        textToUpdate = updateParameter(textToUpdate, &component, paramList[i], attributeList[i]);
    }

    return textToUpdate;
}

QString NetlistUpdater::removeSubcircuitImports(QString param)
{
    QRegularExpressionMatchIterator it = subcircuitRegex.globalMatch(param);
    while (it.hasNext()) {
        param.replace(it.next().captured(0), "");
    }
    return param;
}

QString NetlistUpdater::updateNetlist(QString textToUpdate, QString oldParams, QString newParams)
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
