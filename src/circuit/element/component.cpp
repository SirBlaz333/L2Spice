#include "component.h"

typedef QMap<QString, QString> specialComponentsMap;
Q_GLOBAL_STATIC(specialComponentsMap,
                specialComponents,
                {{"{{MODEL/JJ}}", "model"}, {"{{TRAN}}", "tran"}, {"{{PROBE}}", "probe"}, {"{{METER}}", "meter"}});

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

void Component::setChildProperty(const QString &propertyName, const QString &property)
{
    if (propertyName == "lib_component") {
        libComponent = property;
    } else if (propertyName == "lib_variant") {
        libVariant = property;
    } else if (propertyName == "value") {
        if (specialComponents->contains(property)) {
            elementType = specialComponents->value(property);
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
