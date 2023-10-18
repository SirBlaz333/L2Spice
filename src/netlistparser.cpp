#include "headers/netlistparser.h"

#include <headers/circuit.h>
#include <list>
#include <regex>
#include <set>

std::string NetlistParser::nextWord(std::string::iterator iterator)
{
    std::string result = "";
    while (isWhitespaceCharacter(*iterator) || isQuotes(*iterator)) {
        iterator++;
    }
    while (isWordComponent(*iterator)) {
        result += *iterator;
        iterator++;
    }
    return result;
}

void NetlistParser::parseComponents(std::string::iterator iterator)
{
    while (depth != 0) {
        char current = *iterator;
        if (isLeftParanthesis(current)) {
            depth++;
        } else if (isRightParanthesis(current)) {
            if (depth == 1) {
                currentUuid = "";
            }
            depth--;
        } else if (isWordComponent(current)) {
            processWord(iterator);
        }
        iterator++;
    }
}

void NetlistParser::processWord(std::string::iterator iterator)
{
    std::string word = nextWord(iterator);
    std::set<std::string> elementNames = {"variant", "netclass", "net", "component"};
    if (depth == 1 && elementNames.count(word)) {
        createNewElement(word, nextWord(iterator));
        lastPropertyName = "";
        return;
    }
    if (word == "attribute") {
        return;
    }
    if (lastPropertyName == "") {
        lastPropertyName = word;
        return;
    }
    processProperty(lastPropertyName, word);
}

void NetlistParser::processProperty(std::string propertyName, std::string property)
{
    if (!currentUuid.empty()) {
        Element element = elementMap.at(currentUuid);
        if (attributes.empty()) {
            element.setProperty(propertyName, property);
        } else {
            element.setProperty("attribute", attributes.back());
            attributes.pop_back();
        }
    }
}

void NetlistParser::createNewElement(std::string name, std::string uuid)
{
    Element element;
    if (name == "variant") {
        Element element = Variant();
    } else if (name == "netclass") {
        Element element = NetClass();
    } else if (name == "net") {
        Element element = Net();
    } else if (name == "component") {
        Element element = Component();
    }
    element.setProperty("uuid", uuid);
    elementMap.insert(std::pair<std::string, Element>(uuid, element));
}

bool NetlistParser::isWordComponent(char c)
{
    return std::isalnum(c) || c == '-' || c == '_';
}

bool NetlistParser::isLeftParanthesis(char c)
{
    return c == '(';
}

bool NetlistParser::isRightParanthesis(char c)
{
    return c == ')';
}

bool NetlistParser::isQuotes(char c)
{
    return c == '"';
}

bool NetlistParser::isWhitespaceCharacter(char c)
{
    return std::isspace(c);
}

NetlistParser::NetlistParser() {}

Circuit NetlistParser::parseLibreNotation(std::string input){
    std::string::iterator currentCharacter = input.begin();
    char front = *currentCharacter;
    currentCharacter++;
    if (isLeftParanthesis(front) && nextWord(currentCharacter) == "librepcb_circuit") {
        depth++;
        currentCharacter++;
        parseComponents(currentCharacter);
    }

    std::map<std::string, Net> netMap;
    std::map<std::string, Component> componentMap;
    return Circuit(Variant(), NetClass(), netMap, componentMap);
}
