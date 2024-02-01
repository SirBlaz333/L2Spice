#ifndef LIBRE_NETLIST_UPDATER_H
#define LIBRE_NETLIST_UPDATER_H

#include "src/utils/global_variables.h"

#include <QString>


class LibreNetlistUpdater
{
private:
    int simulatorVersion = SIMULATOR_VERSION_JSIM;
    QString getNewUnit(QString param, QString attribute);
    QString getNewAttribute(QString attribute, QString number, QString unit);
    QMap<QString, QString> getComponents(QString textToUpdate);
    QString updateParameter(QString textToUpdate,
                            QString *component,
                            QString param,
                            QString attribute);
    QString update(QString textToUpdate,
                   QString params,
                   QMap<QString, QString> componentsMap);
    QString removeSubcircuitImports(QString param);
public:
    LibreNetlistUpdater();
    ~LibreNetlistUpdater();
    void setSimulatorVersion(int version);
    QString updateNetlist(QString textToUpdate, QString oldVersion, QString newVersion);
};

#endif // LIBRE_NETLIST_UPDATER_H
