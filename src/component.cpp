#include "../headers/component.h"

std::string Component::getLibComponent() const
{
    return libComponent;
}

std::string Component::getLibVariant() const
{
    return libVariant;
}

std::string Component::getValue() const
{
    return value;
}

bool Component::getLockAssembly() const
{
    return lockAssembly;
}

std::list<Attribute> Component::getAttributeList() const
{
    return attributeList;
}
std::list<Signal> Component::getSignalList() const
{
    return signalList;
}

const Device Component::getDevice() const
{
    return *device;
}

void Component::setChildProperty(const std::string &propertyName, const std::string &property)
{
    if (propertyName == "lib_component") {
        libComponent = property;
    } else if (propertyName == "lib_variant") {
        libVariant = property;
    } else if (propertyName == "value") {
        value = property;
    } else if (propertyName == "lock_assembly") {
        lockAssembly = (property == "true");
    }
}
void Component::setProperty(const std::string &propertyName, const Element* property)
{
    if (propertyName == "attribute") {
        const Attribute* attribute = dynamic_cast<const Attribute*>(property);
        if (attribute->getName() == "SOURCETYPE" && attribute->getValue() == "JJ") {
            elementType = "model";
        }
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
