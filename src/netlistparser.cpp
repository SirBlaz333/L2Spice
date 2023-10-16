#include "headers/netlistparser.h"

#include <headers/circuit.h>
#include <list>
#include <regex>

std::string NetlistParser::nextWord(std::string::iterator iterator)
{
    std::string result = "";
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

    return Circuit(variant, netClass, netMap, componentMap);
}
