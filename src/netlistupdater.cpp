#include "../headers/netlistupdater.h"
#include "headers/attributeutils.h"
#include <QList>
#include <QMap>
#include <QRegularExpression>
#include <functional>
#include <iostream>
#include <regex>

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

std::string findTextByPattern(const std::string &text, const std::string &pattern)
{
    std::regex regexPattern(pattern);
    std::smatch match;

    // Try to match the pattern in the text
    if (std::regex_search(text, match, regexPattern)) {
        // match[0] contains the entire matched text
        return match.str();
    } else {
        return ""; // Return an empty string if no match is found
    }
}

QString getSubString(QString pattern, QString input, int captureGroup) {
    QRegularExpression nameRegex(pattern);
    QRegularExpressionMatch nameMatch = nameRegex.match(input);
    return nameMatch.captured(captureGroup);
}

QMap<QString, QString> getComponents(QString textToUpdate)
{
    QMap<QString, QString> map;
    QRegularExpression pattern(R"(\(component.+?\n\s\))",
                               QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator it = pattern.globalMatch(textToUpdate);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString result = match.captured(0);
        QString namePattern = R"(\(name \"(.+?)\"\))";
        QString name = getSubString(namePattern, result, 1);
        map[name] = result;
    }

    return map;
}

QString update(QString textToUpdate, QString params, QMap<QString, QString> componentsMap)
{
    QList<QString> paramList = splitParams(params.begin(), params.end());
    QString name = paramList[0];
    paramList.erase(paramList.begin(), paramList.begin() + 3);
    //check if the first character in first attribute is a number or not
    //if it is not, that it is a text parameter and we don't need to modify it for now
    if (paramList.empty()) {
        return textToUpdate;
    }
    if (!paramList.first()[0].isDigit()) {
        paramList.removeFirst();
    }
    QString attributePattern
        = R"(\(attribute \"\w+\" \(type \w+\) \(unit (\w+)\) \(value \"(\d+)\"\)\))";
    QRegularExpression attributeRegex(attributePattern);
    QRegularExpressionMatchIterator it = attributeRegex.globalMatch(componentsMap[name]);
    QList<QString> list;
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        list.append(match.captured(0));
    }
    QString paramPattern = R"((\d+)(\w*))";
    for (int i = 0; i < paramList.size(); i++) {
        QString param = paramList[i];
        QString attribute = list[i];
        QString oldAttribute = attribute;
        QString number = getSubString(paramPattern, param, 1);
        QString unitPrefix = attribute_utils::getFullUnitPrefix(
            getSubString(paramPattern, param, 2));
        QString unit = getSubString(attributePattern, attribute, 1);
        QString unitWithoutPrefix = attribute_utils::getUnitWithoutPrefix(unit);
        unit = unitPrefix + unitWithoutPrefix;
        QRegularExpressionMatch match = attributeRegex.match(attribute);
        QStringList capturedText = match.capturedTexts();
        attribute.replace(capturedText.at(1), unit);
        attribute.replace(capturedText.at(2), number);
        QString oldComponent = componentsMap[name];
        QString updatedComponent = componentsMap[name];
        updatedComponent.replace(oldAttribute, attribute);
        QString newText = textToUpdate;
        newText.replace(oldComponent, updatedComponent);
        textToUpdate = newText;
    }

    return textToUpdate;
}

QString NetlistUpdater::updateNetlist(QString textToUpdate,
                                          QString oldParams,
                                          QString newParams)
{
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
