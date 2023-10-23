#include "headers/netlistparser.h"

#include <headers/circuit.h>
#include <iostream>
#include <list>
#include <regex>
#include <set>

std::string NetlistParser::nextWord()
{
    if (isQuotes(*currentCharacter)) {
        return nextDataInQuotes();
    }
    std::string result = "";
    while (isWordComponent(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    return result;
}

std::string NetlistParser::nextDataInQuotes()
{
    std::string result = "";
    currentCharacter++;
    while (!isQuotes(*currentCharacter)) {
        result += *currentCharacter;
        currentCharacter++;
    }
    currentCharacter++;
    return result;
}

void NetlistParser::parseComponents(std::string::iterator last)
{
    while (currentCharacter != last) {
        parseComponent("", last);
        currentCharacter++;
    }
}

void NetlistParser::parseComponent(std::string parentUuid,
                                   std::string::iterator last)
{
    while (currentCharacter != last) {
        if (isLeftParanthesis(*currentCharacter)) {
            parseElement(parentUuid, last);
        }
        if (isRightParanthesis(*currentCharacter)) {
            return;
        }
        currentCharacter++;
    }
}

void NetlistParser::parseElement(std::string parentUuid,
                                 std::string::iterator last)
{
    currentCharacter++;
    std::string name = nextWord();
    currentCharacter++;
    std::string value = nextWord();
    if (isRightParanthesis(*currentCharacter)) {
        Element* element = elementMap[parentUuid].get();
        element->setProperty(name, value);
        currentCharacter++;
        return;
    }
    if (isWhitespaceCharacter(*currentCharacter)) {
        createNewElement(name, value);
        Element *newElement = elementMap[value].get();
        parseComponent(value, last);
        if (!parentUuid.empty()) {
            Element* element = elementMap[parentUuid].get();
            element->setProperty(name, newElement);
        }
    }
}

void NetlistParser::createNewElement(std::string name, std::string uuid)
{
    if (name == "variant") {
        elementMap[uuid] = std::make_unique<Variant>();
    } else if (name == "netclass") {
        elementMap[uuid] = std::make_unique<NetClass>();
    } else if (name == "net") {
        elementMap[uuid] = std::make_unique<Net>();
    } else if (name == "component") {
        elementMap[uuid] = std::make_unique<Component>();
    } else if (name == "attribute") {
        uuid = createUuid();
        elementMap[uuid] = std::make_unique<Attribute>();
    }
    elementMap[uuid].get()->setProperty("uuid", uuid);
}

std::string NetlistParser::createUuid()
{
    return "";
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

NetlistParser::~NetlistParser() {}

Circuit NetlistParser::parseLibreNotation(std::string input)
{
    currentCharacter = input.begin();
    char front = *currentCharacter;
    currentCharacter++;
    if (isLeftParanthesis(front) && nextWord() == "librepcb_circuit") {
        currentCharacter++;
        parseComponents(input.end());
    }

    std::map<std::string, Net> netMap;
    std::map<std::string, Component> componentMap;

//    Element *element = elementMap.begin()->second.get();
//    Variant *variant = dynamic_cast<Variant *>(element);

    Circuit circuit = Circuit(Variant(), NetClass(), netMap, componentMap);
    return circuit;
}
