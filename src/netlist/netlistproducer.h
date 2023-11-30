#ifndef NETLISTPRODUCER_H
#define NETLISTPRODUCER_H

#include <src/circuit/circuit.h>

class NetlistProducer
{
private:
    static const QRegularExpression subcircuitIdentifierRegex;
    void writeSubcircuit(QMap<QString, QString> *subcircuits, QString subcircuitName);
    void writeSubcircuit(QMap<QString, QString> *subcircuits, Component component);
    QString getAllSubcircuits(QSet<QString> usedComponents, QMap<QString, Component> componentMap);
public:
    NetlistProducer();
    ~NetlistProducer();
    QString produceSpiceNotationNetlist(const Circuit &circuit);
};

#endif // NETLISTPRODUCER_H
