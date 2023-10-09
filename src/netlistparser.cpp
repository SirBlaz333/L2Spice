#include "headers/netlistparser.h"

#include <headers/circuit.h>
#include <regex>

NetlistParser::NetlistParser() {}

Circuit NetlistParser::parseLibreNotation(std::string input){
}

bool hasMatches(std::string input, std::regex regex)
{
    return std::regex_search(input, regex);
}

bool isMatch(std::string input, std::regex regex)
{
    return std::regex_match(input, regex);
}

std::vector<std::string> findAllMatches(std::string input, std::regex regex)
{
    std::vector<std::string> vector;
    std::smatch match;
    while (std::regex_search(input, match, regex)) {
        vector.push_back(match.suffix().str());
    }
    return vector;
}
