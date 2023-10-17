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
void Component::setProperty(const std::string &propertyName, const Element &property)
{
    if (propertyName == "signal") {
        signalList.push_back(*((Signal *) &property));
    }
}

Component::Component() {}

Component::~Component() {}
