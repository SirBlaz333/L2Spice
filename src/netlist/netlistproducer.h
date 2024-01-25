#ifndef NETLISTPRODUCER_H
#define NETLISTPRODUCER_H

#include "src/netlist/componentprinter.h"
#include <src/app/conversionparams.h>
#include <src/circuit/circuit.h>

class NetlistProducer
{
private:
    ComponentPrinter componentPrinter;
    QString writeComponents(QString parentSignalUuid,
                            Component component,
                            QMap<QString, QSet<Component>> netComponentsMap,
                            QMap<QString, QString> netLabelMap,
                            QSet<QString> *usedComponents);

public:
    NetlistProducer();
    ~NetlistProducer();
    QString produceSpiceNotationNetlist(const Circuit &circuit, const ConversionParams &params);
};

#endif // NETLISTPRODUCER_H
