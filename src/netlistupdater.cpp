#include "../headers/netlistupdater.h"
#include "headers/attributeutils.h"
#include <QList>
#include <QRegularExpression>
#include <functional>
#include <iostream>
#include <regex>
#include <vector>

NetlistUpdater::NetlistUpdater() {}

NetlistUpdater::~NetlistUpdater() {}

std::vector<std::string> split(std::string::iterator iterator,
                                 std::string::iterator end,
                                 std::function<bool(char)> test)
{
    std::vector<std::string> vector;
    std::string result;
    while (iterator != end) {
        if (test(*iterator) && !result.empty()) {
            vector.push_back(result);
            result = "";
        } else {
            result += *iterator;
        }
        iterator++;
    }
    if (!result.empty()) {
        vector.push_back(result);
    }
    return vector;
}

std::vector<std::string> splitRows(std::string::iterator iterator, std::string::iterator end)
{
    return split(iterator, end, [](char c) { return c == '\n'; });
}

std::vector<std::string> splitParams(std::string::iterator iterator, std::string::iterator end){
    return split(iterator, end, [](char c) { return c == ' ' || c == '(' || c == ')'; });
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

std::map<std::string, QString> getComponents(std::string textToUpdate)
{
    std::map<std::string, QString> map;
    QRegularExpression pattern(R"(\(component.+?\n\s\))",
                               QRegularExpression::DotMatchesEverythingOption);
    QRegularExpressionMatchIterator it = pattern.globalMatch(QString::fromStdString(textToUpdate));
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        QString result = match.captured(0);
        std::string namePattern = R"(\(name \"(.+?)\"\))";
        std::string name = getSubString(QString::fromStdString(namePattern), result, 1).toStdString();
        map[name] = result;
    }

    return map;
}

std::string update(std::string textToUpdate, std::string params, std::map<std::string, QString> componentsMap)
{
    std::vector<std::string> paramVector = splitParams(params.begin(), params.end());
    std::string name = paramVector[0];
    for (int i = 0; i < 3; i++) {
        paramVector.erase(paramVector.begin());
    }
    //check if the first character in first attribute is a number or not
    //if it is not, that it is a text parameter and we don't need to modify it for now
    if (paramVector.empty()) {
        return textToUpdate;
    }
    if (!std::isdigit(paramVector[0][0])) {
        paramVector.erase(paramVector.begin());
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
    for (int i = 0; i < paramVector.size(); i++) {
        QString param = QString::fromStdString(paramVector[i]);
        QString attribute = list[i];
        QString oldAttribute = attribute;
        QString number = getSubString(paramPattern, param, 1);
        std::string unitPrefix = attribute_utils::getFullUnitPrefix(
            getSubString(paramPattern, param, 2).toStdString());
        QString unit = getSubString(attributePattern, attribute, 1);
        std::string unitWithoutPrefix = attribute_utils::getUnitWithoutPrefix(unit.toStdString());
        unit = QString::fromStdString(unitPrefix + unitWithoutPrefix);
        QRegularExpressionMatch match = attributeRegex.match(attribute);
        QStringList capturedText = match.capturedTexts();
        attribute.replace(capturedText.at(1), unit);
        attribute.replace(capturedText.at(2), number);
        QString oldComponent = componentsMap[name];
        QString updatedComponent = componentsMap[name];
        updatedComponent.replace(oldAttribute, attribute);
        QString newText = QString::fromStdString(textToUpdate);
        newText.replace(oldComponent, updatedComponent);
        textToUpdate = newText.toStdString();
    }

    return textToUpdate;
}

std::string NetlistUpdater::updateNetlist(std::string textToUpdate,
                                          std::string oldParams,
                                          std::string newParams)
{
    std::vector<std::string> oldRows = splitRows(oldParams.begin(), oldParams.end());
    std::vector<std::string> newRows = splitRows(newParams.begin(), newParams.end());
    std::map<std::string, QString> componentsMap = getComponents(textToUpdate);
    if (oldRows.size() != newRows.size()) {
        return "";
    }
    unsigned int i = 0;
    while (i < oldRows.size()) {
        std::string oldRow = oldRows[i];
        std::string newRow = newRows[i];
        if (oldRow != newRow) {
            textToUpdate = update(textToUpdate, newRow, componentsMap);
        }
        i++;
    }
    return textToUpdate;
}
