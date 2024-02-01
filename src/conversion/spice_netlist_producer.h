#ifndef SPICE_NETLIST_PRODUCER_H
#define SPICE_NETLIST_PRODUCER_H

#include "src/conversion/output/spice_printer.h"
#include <src/conversion/data/conversion_params.h>
#include <src/circuit/circuit.h>

class SpiceNetlistProducer
{
private:
    QString writeComponents(QString parentSignalUuid,
                            Component component,
                            SpicePrinter printer,
                            QMap<QString, QSet<Component>> netComponentsMap,
                            QSet<QString> *usedComponents);

public:
    SpiceNetlistProducer();
    ~SpiceNetlistProducer();
    QString produceSpiceNotationNetlist(const Circuit &circuit, const ConversionParams &params);
};

#endif // SPICE_NETLIST_PRODUCER_H
