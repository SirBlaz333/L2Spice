#ifndef SPICENETLISTPRODUCER_H
#define SPICENETLISTPRODUCER_H

#include "src/netlist/componentprinter.h"
#include <src/app/conversionparams.h>
#include <src/circuit/circuit.h>

class SpiceNetlistProducer
{
private:
    ComponentPrinter componentPrinter;
    QString writeComponents(QString parentSignalUuid,
                            Component component,
                            QMap<QString, QSet<Component>> netComponentsMap,
                            QMap<QString, QString> netLabelMap,
                            QSet<QString> *usedComponents);

public:
    SpiceNetlistProducer();
    ~SpiceNetlistProducer();
    QString produceSpiceNotationNetlist(const Circuit &circuit, const ConversionParams &params);
};

#endif // SPICENETLISTPRODUCER_H