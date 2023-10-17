#ifndef NETLISTPARSER_H
#define NETLISTPARSER_H

#include "circuit.h"
#include "variant.h"
#include "headers/component.h"
#include "headers/net.h"
#include <list>


class NetlistParser
{
private:
    int depth = 0;
    std::string lastElementName;
    std::string lastPropertyName;
    std::map<std::string, std::map<std::string, std::string>> elementMap;
    std::map<std::string, Net> netMap;
    std::map<std::string, Component> componentMap;

    std::string nextWord(std::string::iterator iterator);
    void parseComponents(std::string::iterator iterator);
    void processWord(std::string::iterator iterator);
    void processProperty(std::string property);
    bool isWordComponent(char c);
    bool isLeftParanthesis(char c);
    bool isRightParanthesis(char c);
    bool isQuotes(char c);
    bool isWhitespaceCharacter(char c);
public:
    NetlistParser();
    ~NetlistParser();
    Circuit parseLibreNotation(std::string input);
};

#endif // NETLISTPARSER_H
