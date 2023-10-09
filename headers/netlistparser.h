#ifndef NETLISTPARSER_H
#define NETLISTPARSER_H

#include "circuit.h"



class NetlistParser
{
public:
    NetlistParser();
    ~NetlistParser();
    Circuit parseLibreNotation(std::string input);
};

#endif // NETLISTPARSER_H
