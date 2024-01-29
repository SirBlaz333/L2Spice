#ifndef SPICENETLISTPRODUCER_H
#define SPICENETLISTPRODUCER_H

#include "src/conversion/output/spiceprinter.h"
#include <src/conversion/data/conversionparams.h>
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

#endif // SPICENETLISTPRODUCER_H
