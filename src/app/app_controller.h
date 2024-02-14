#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <src/conversion/data/conversion_params.h>
#include <src/conversion/libre_netlist_parser.h>
#include <src/conversion/libre_netlist_updater.h>
#include <src/conversion/spice_netlist_producer.h>
/**
 * AppController is used to create a SPICE netlist from LibrePCB circuit file and
 * update the values in LibrePCB circuit using new assigned values in SPICE netlist.
 *
 */
class AppController
{
private:
    LibreNetlistParser parser;
    SpiceNetlistProducer producer;
    LibreNetlistUpdater updater;

public:
    /**
     * Creates LibrePCB circuit into the SPICE netlist.
     *
     * @param libreNetlist - LibrePCB circuit.
     * @param params - instance of ConversionParams class, that contains desired parameters for the conversion.
     * @return SPICE netlist.
     */
    QString convertToSpice(QString libreNetlist, ConversionParams &params);

    /**
     * Updates the LibrePCB netlist using values from SPICE notation.
     *
     * @param libreNetlist - initial LibrePCB circuit.
     * @param spiceNetlist - SPICE netlist.
     * @return updated LibrePCB circuit.
     */
    QString updateLibre(QString libreNetlist, QString spiceNetlist);
};

#endif // APP_CONTROLLER_H
