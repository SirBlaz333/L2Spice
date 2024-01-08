#include "component.h"
#include "src/utils/attributeutils.h"

QString Component::getLibComponent() const
{
    return libComponent;
}

QString Component::getLibVariant() const
{
    return libVariant;
}

QString Component::getValue() const
{
    return value;
}

bool Component::getLockAssembly() const
{
    return lockAssembly;
}

QList<Attribute> Component::getAttributeList() const
{
    return attributeList;
}

bool Component::removeAttribute(const Attribute attribute)
{
    return attributeList.removeOne(attribute);
}
QList<Signal> Component::getSignalList() const
{
    return signalList;
}

const Device Component::getDevice() const
{
    return *device;
}

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

QString printTran(Component tran) {
    return "\n.tran " + attributeUtils::writeAttributes(tran, false);
}

QString Component::print(QString parentUUID) const
{
    if (elementType == "component") {
        return printComponent(*this, parentUUID, netLabelMap);
    }
    if (elementType == "model") {
        return printModel(*this);
    }
    if (elementType == "tran") {
        return printTran(*this);
    }
    return "";
}

void Component::setNetLabelMap(QMap<QString, QString> map)
{
    netLabelMap = map;
}

void Component::setChildProperty(const QString &propertyName, const QString &property)
{
    if (propertyName == "lib_component") {
        libComponent = property;
    } else if (propertyName == "lib_variant") {
        libVariant = property;
    } else if (propertyName == "value") {
        if (property == "{{MODEL/JJ}}") {
            elementType = "model";
        }
        if (property == "{{TRAN}}") {
            elementType = "tran";
        }
        value = property;
    } else if (propertyName == "lock_assembly") {
        lockAssembly = (property == "true");
    }
}
void Component::setProperty(const QString &propertyName, const Element* property)
{
    if (propertyName == "attribute") {
        const Attribute* attribute = dynamic_cast<const Attribute*>(property);
        attributeList.push_back(*attribute);
    }
    if (propertyName == "signal") {
        const Signal* signal = dynamic_cast<const Signal*>(property);
        signalList.push_back(*signal);
    }
    if (propertyName == "device") {
        device = dynamic_cast<const Device*>(property);
    }
}

Component::Component()
{
    elementType = "component";
}

Component::~Component() {}
