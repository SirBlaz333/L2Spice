#ifndef SPICE_NETLIST_PRODUCER_H
#define SPICE_NETLIST_PRODUCER_H

#include "src/conversion/output/spice_printer.h"
#include <src/conversion/data/conversion_params.h>
#include <src/circuit/circuit.h>

/**
 * SpiceNetlistProducer is used to produce a SPICE netlist from the Circuit object and with given params.
 */
class SpiceNetlistProducer
{
private:
    QString writeComponents(QString parentSignalUuid,
                            Component component,
                            SpicePrinter printer,
                            QMap<QString, QSet<Component>> netComponentsMap,
                            QSet<QString> *usedComponents);

public:
    /**
     * Creates a SPICE netlist.
     *
     * @param circuit - instance of the Circuit class.
     * @param params - instance of the ConversionParams class.
     * @return SPICE netlist.
     */
    QString produceSpiceNetlist(const Circuit &circuit, const ConversionParams &params);
};

#endif // SPICE_NETLIST_PRODUCER_H
