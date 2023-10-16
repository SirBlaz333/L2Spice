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
    Variant *variant = NULL;
    NetClass *netClass = NULL;
    std::map<std::string, Net> netMap;
    std::map<std::string, Component> componentMap;
    int depth = 0;

    std::string nextWord(std::string::iterator iterator);
    void parseComponents(std::string::iterator iterator);
    void processWord(std::string::iterator iterator);
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
