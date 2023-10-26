#ifndef NETLISTPRODUCER_H
#define NETLISTPRODUCER_H

#include "circuit.h"

class NetlistProducer
{
private:
    std::string getValueOrDefault(std::string string);
    std::string createSourceType(std::string name, std::list<Attribute> attributeList);

public:
    NetlistProducer();
    ~NetlistProducer();
    std::string produceSpiceNotationNetlist(const Circuit &circuit);
};

#endif // NETLISTPRODUCER_H
