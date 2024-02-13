#ifndef APP_CONTROLLER_H
#define APP_CONTROLLER_H

#include <src/conversion/data/conversion_params.h>
#include <src/conversion/libre_netlist_parser.h>
#include <src/conversion/libre_netlist_updater.h>
#include <src/conversion/spice_netlist_producer.h>

class AppController
{
private:
    LibreNetlistParser parser;
    SpiceNetlistProducer producer;
    LibreNetlistUpdater updater;

public:
    AppController();
    ~AppController();
    QString convertToSpice(QString libreNotation, ConversionParams &params);
    QString updateLibre(QString oldLibreNotation, QString newSpiceNotation);
};

#endif // APP_CONTROLLER_H
