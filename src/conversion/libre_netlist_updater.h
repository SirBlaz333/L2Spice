#ifndef LIBRE_NETLIST_UPDATER_H
#define LIBRE_NETLIST_UPDATER_H

#include "src/utils/global_variables.h"

#include <QString>

/**
 * LibreNetlistUpdatar is used to update the LibrePCB circuit from the SPICE netlist.
 */
class LibreNetlistUpdater
{
private:
    int simulatorVersion = GlobalVariables::SIMULATOR_VERSION_JSIM;
    QString getNewUnit(QString param, QString attribute);
    QString getNewAttribute(QString attribute, QString number, QString unit);
    QMap<QString, QString> getComponents(QString textToUpdate);
    QString updateAttribute(QString textToUpdate,
                            QString *component,
                            QString param,
                            QString attribute);
    QString update(QString textToUpdate,
                   QString params,
                   QMap<QString, QString> componentsMap);
    QString removeSubcircuitImports(QString param);
public:
    /**
     * Sets the current simulator version.
     * @param version - new simulator version.
     */
    void setSimulatorVersion(int version);

    /**
     * Updates the LibrePCB circuit using values from the SPICE netlits.
     *
     * @param libreNetlist - old LibrePCB circuit.
     * @param spiceNetlist - new SPICE netlist.
     * @return updated version of LibrePCB circuit.
     */
    QString updateNetlist(QString libreNetlist, QString spiceNetlist);
};

#endif // LIBRE_NETLIST_UPDATER_H
