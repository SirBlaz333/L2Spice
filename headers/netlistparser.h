#ifndef NETLISTPARSER_H
#define NETLISTPARSER_H

#include "circuit.h"
#include <list>
#include <vector>


class NetlistParser
{
private:
    int depth = 0;
    std::string currentUuid;
    std::string lastElementName;
    std::string lastPropertyName;
    std::map<std::string, Element> elementMap;
    std::list<Attribute> attributes;

    std::string nextWord(std::string::iterator iterator);
    void parseComponents(std::string::iterator iterator, std::string::iterator last);
    void processWord(std::string::iterator iterator);
    void processProperty(std::string propertyName, std::string property);
    void createNewElement(std::string name, std::string uuid);
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
