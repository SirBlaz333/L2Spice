#include "componentprinter.h"
#include "src/utils/attributeutils.h"

ComponentPrinter::ComponentPrinter(QMap<QString, QString> map)
{
    this->netLabelMap = map;
}

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
    for (Signal signal : component.getSignalList()) {
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

QString ComponentPrinter::printOutput(Component component)
{
    if (component.getElementType() == "probe") {
        QString result = ".PRINT " + attributeUtils::writeAttributes(component, false) + " ";
        for (Signal signal : component.getSignalList()) {
            result += writeSignal(signal.getNet().getUuid(), netLabelMap);
        }
        return result + "\n";
    }
    return component.getName() + "\n";
}
