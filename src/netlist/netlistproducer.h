#ifndef NETLISTPRODUCER_H
#define NETLISTPRODUCER_H

#include <src/circuit/circuit.h>

class NetlistProducer
{
public:
    NetlistProducer();
    ~NetlistProducer();
    QString produceSpiceNotationNetlist(const Circuit &circuit);
};

#endif // NETLISTPRODUCER_H
