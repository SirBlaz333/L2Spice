#include "componentprinter.h"
#include "src/utils/attributeutils.h"

ComponentPrinter::ComponentPrinter(const QMap<QString, QString> &netLabelMap,
                                   const QMap<QString, QSet<Component> > &netComponentsMap)
    : netLabelMap(netLabelMap)
    , netComponentsMap(netComponentsMap)
{}

ComponentPrinter::ComponentPrinter() {}

ComponentPrinter::~ComponentPrinter() {}

QString writeSignal(QString uuid, QMap<QString, QString> netLabelMap)
{
    return uuid.isEmpty() || netLabelMap.isEmpty() ? "_ " : netLabelMap[uuid] + " ";
}

QString printComponent(Component component, QString parentUUID, QMap<QString, QString> netLabelMap)
{
    QString result = component.getName() + " ";
    QList<Attribute> list = component.getAttributeList();
    if (component.getValue() == "{{SUBCIRCUIT}}") {
        result = "X" + list.first().getValue().toUpper() + " " + result;
        component.removeAttribute(list.first());
    }
    if (!parentUUID.isEmpty()) {
        result += writeSignal(parentUUID, netLabelMap);
    }
    for (Signal &signal : component.getSignalList()) {
        if (signal.getNet().getUuid() != parentUUID) {
            result += writeSignal(signal.getNet().getUuid(), netLabelMap);
        }
    }
    if (component.getValue() == "VCC") {
        result += "0 ";
    }
    result += attributeUtils::writeAttributes(component, false);
    return result;
}

QString printModel(Component model)
{
    return ".MODEL " + model.getName() + " " + attributeUtils::writeAttributes(model, true);
}

QString printTran(Component tran)
{
    return "\n.tran " + attributeUtils::writeAttributes(tran, false);
}

QString ComponentPrinter::print(Component component, QString parentUUID)
{
    QString elementType = component.getElementType();
    if (elementType == "component") {
        return printComponent(component, parentUUID, netLabelMap);
    }
    if (elementType == "model") {
        return printModel(component);
    }
    if (elementType == "tran") {
        return printTran(component);
    }
    return "";
}

QString printProbe(Component component, QMap<QString, QString> netLabelMap) {
    return ".PRINT "
           + attributeUtils::writeAttributes(component, false) + " "
           + writeSignal(component.getSignalList().constFirst().getNet().getUuid(), netLabelMap)
           + "0";
}


QString getNodevMode(Attribute printType)
{
    if (printType.getValue() == "PHASE") {
        return ".PRINT NODEP ";
    }
    return ".PRINT NODEV ";
}

QString printNodev(Attribute printType, QMap<QString, QString> netLabelMap, QString firstUuid, QString secondUuid) {
    return getNodevMode(printType) + netLabelMap.value(firstUuid) + " " + netLabelMap.value(secondUuid);
}

QString printMeter(Component component,
                   QMap<QString, QString> netLabelMap,
                   QMap<QString, QSet<Component>> netComponentsMap)
{
    QString firstUuid = component.getSignalList().constFirst().getNet().getUuid();
    QString secondUuid = component.getSignalList().constLast().getNet().getUuid();
    QSet<Component> first = netComponentsMap.value(firstUuid);
    QSet<Component> second = netComponentsMap.value(secondUuid);
    Attribute device, printType;
    for (Attribute &attribute : component.getAttributeList()) {
        if (attribute.getName() == "DEVICE_NAME") {
            device = attribute;
        }
        if (attribute.getName() == "PRINT_TYPE") {
            printType = attribute;
        }
    }
    if (first.isEmpty() || second.isEmpty()) {
        return printNodev(printType, netLabelMap, firstUuid, secondUuid);
    }
    QList<Component> intersection;
    for (const Component &component : first) {
        if (second.contains(component)) {
            intersection.append(component);
        }
    }
    if (intersection.size() != 1) {
        return printNodev(printType, netLabelMap, firstUuid, secondUuid);
    }
    if (!device.getValue().isEmpty() && device.getValue() != intersection.first().getName()) {
        return printNodev(printType, netLabelMap, firstUuid, secondUuid);
    }
    return ".PRINT " + printType.getValue() + " " + intersection.first().getName();
}

QString ComponentPrinter::printOutput(Component component)
{
    if (component.getElementType() == "probe") {
        return printProbe(component, netLabelMap) + "\n";
    }
    if (component.getElementType() == "meter") {
        return printMeter(component, netLabelMap, netComponentsMap) + "\n";
    }
    return "";
}
