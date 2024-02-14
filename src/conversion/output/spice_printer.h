#ifndef SPICE_PRINTER_H
#define SPICE_PRINTER_H

#include <QMap>
#include <QSet>
#include <QString>

#include <src/circuit/element/component.h>
#include <src/conversion/data/conversion_params.h>

/**
 * SpicePrinter is used to create a string representation of the SPICE netlist component.
 */
class SpicePrinter
{
private:
    QMap<QString, QString> netLabelMap;
    QMap<QString, QSet<Component>> netComponentsMap;
    ConversionParams params;
    QString printOutput(Component component);
    QString printMeter(Component component);
    QString printProbe(Component component);
    QString printModel(Component component);
    QString printComponent(Component component, QString parentUUID);

public:
    /**
     * @param netLabelMap - map where the key is the net uuid from LibrePCB circuit
     * and the value is the corresponding net name in SPICE netlist.
     * @param netComponentsMap - map where the key is the key is the net uuid and the
     * value is the set of the components connected to that net.
     * @param params - an instances of the ConversionParams class used for the conversion.
     */
    SpicePrinter(const QMap<QString, QString> &netLabelMap,
                 const QMap<QString, QSet<Component>> &netComponentsMap,
                 const ConversionParams &params);

    /**
     * Creates a string representation for the component.
     *
     * @param component - the component to print.
     * @param parentUUID - the uuid of the parent component. If empty, than parent component doesn't exist.
     * return a string representation of the given component.
     */
    QString print(Component component, QString parentUUID = QString());

    /**
     * Creates a string representation for the list of the SPICE outputs.
     *
     * @param components - the list of the components.
     * return a string representation of the given list of the SPICE outputs.
     */
    QString printOutputs(QList<Component> components);
};

#endif // SPICE_PRINTER_H
