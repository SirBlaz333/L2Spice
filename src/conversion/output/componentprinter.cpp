#include "componentprinter.h"
#include "src/utils/attributeutils.h"

Q_GLOBAL_STATIC(QString, EMPTY_STRING, QString());
Q_GLOBAL_STATIC(QString, MODEL, QString(".MODEL %1 %2"));
Q_GLOBAL_STATIC(QString, TRAN, QString("\n.tran %1"));
Q_GLOBAL_STATIC(QString, PROBE, QString(".PRINT %1 %2 0\n"));
Q_GLOBAL_STATIC(QString, METER, QString(".PRINT %1 %2\n"));
Q_GLOBAL_STATIC(QString, NODEV, QString(".PRINT NODEV %1 %2\n"));
Q_GLOBAL_STATIC(QString, NODEP, QString(".PRINT NODEP %1 %2\n"));

ComponentPrinter::ComponentPrinter(const QMap<QString, QString> &netLabelMap,
                                   const QMap<QString, QSet<Component> > &netComponentsMap,
                                   const ConversionParams &params)
    : netLabelMap(netLabelMap)
    , netComponentsMap(netComponentsMap)
    , params(params)
{}

ComponentPrinter::ComponentPrinter() {}

ComponentPrinter::~ComponentPrinter() {}

QString writeSignal(QString uuid, QMap<QString, QString> netLabelMap)
{
    return uuid.isEmpty() || netLabelMap.isEmpty() ? "_ " : netLabelMap[uuid];
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
        result += writeSignal(parentUUID, netLabelMap) + " ";
    }
    for (Signal &signal : component.getSignalList()) {
        if (signal.getNet().getUuid() != parentUUID) {
            result += writeSignal(signal.getNet().getUuid(), netLabelMap) + " ";
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
    return MODEL->arg(model.getName(), attributeUtils::writeAttributes(model, true));
}

QString printTran(Component tran)
{
    return TRAN->arg(attributeUtils::writeAttributes(tran, false));
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
    return *EMPTY_STRING;
}

QString printProbe(Component component, QMap<QString, QString> netLabelMap) {
    Attribute printType;
    for (Attribute &attribute : component.getAttributeList()) {
        if (attribute.getName() == "PRINT_TYPE") {
            printType = attribute;
        }
    }
    QString signal = writeSignal(component.getSignalList().constFirst().getNet().getUuid(), netLabelMap);
    return PROBE->arg(printType.getValue(), signal);
}


QString* getNodevMode(Attribute printType)
{
    if (printType.getValue() == "PHASE") {
        return NODEP;
    }
    return NODEV;
}

QString printNodev(Attribute printType, QMap<QString, QString> netLabelMap, QString firstUuid, QString secondUuid) {
    return getNodevMode(printType)->arg(netLabelMap.value(firstUuid), netLabelMap.value(secondUuid));
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
    if (intersection.size() != 1
        || (!device.getValue().isEmpty() && device.getValue() != intersection.first().getName())) {
        return printNodev(printType, netLabelMap, firstUuid, secondUuid);
    }
    return METER->arg(printType.getValue(), intersection.first().getName());
}

QString ComponentPrinter::printOutput(Component component) {
    if (component.getElementType() == "probe") {
        return printProbe(component, netLabelMap);
    }
    if (component.getElementType() == "meter") {
        return printMeter(component, netLabelMap, netComponentsMap);
    }
    return *EMPTY_STRING;
}

QString ComponentPrinter::printOutputs(QList<Component> components)
{
    QMap<QString, QList<Component>> fileOutputsMap;
    for (Component &component : components) {
        QString fileName = *EMPTY_STRING;
        for (Attribute &attribute : component.getAttributeList()) {
            if (attribute.getName() == "FILENAME") {
                fileName = attribute.getValue();
            }
        }
        QList<Component> assignedComponents = fileOutputsMap.value(fileName);
        assignedComponents.append(component);
        fileOutputsMap.insert(fileName, assignedComponents);
    }
    QString result;
    QList<QString> fileNames = fileOutputsMap.keys();
    fileNames.sort();
    for (QString &fileName : fileNames) {
        if (!fileName.isEmpty()) {
            result += ".FILE " + fileName + "\n";
        }
        for (Component &component : fileOutputsMap.value(fileName)) {
            result += printOutput(component);
        }
    }
    return result;
}
