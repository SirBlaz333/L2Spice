#ifndef NETLISTPRODUCER_H
#define NETLISTPRODUCER_H

#include <src/circuit/circuit.h>

class NetlistProducer
{
private:
    QString getValueOrDefault(QString string);
    QString createSourceType(QString name, QList<Attribute> attributeList);

public:
    NetlistProducer();
    ~NetlistProducer();
    QString produceSpiceNotationNetlist(const Circuit &circuit);
};

#endif // NETLISTPRODUCER_H
