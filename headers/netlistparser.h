#ifndef NETLISTPARSER_H
#define NETLISTPARSER_H

#include <headers/circuit.h>
#include <iostream>
#include <list>
#include <regex>
#include <set>
#include <list>
#include <vector>
#include <bits/unique_ptr.h>


class NetlistParser
{
private:
    std::map<std::string, std::function<std::unique_ptr<Element>()>> elementFactory;
    std::string::iterator currentCharacter;
    std::map<std::string, std::unique_ptr<Element>> elementMap;

    std::string nextWord();
    std::string nextDataInQuotes();
    void parseComponents(std::string::iterator last);
    void parseComponent(std::string parentUuid,  std::string::iterator last);
    Element* createNewElement(std::string name, std::string uuid);
    void parseElement(std::string parentUuid, std::string::iterator last);
public:
    NetlistParser();
    ~NetlistParser();
    Circuit parseLibreNotation(std::string input);
};

#endif // NETLISTPARSER_H
