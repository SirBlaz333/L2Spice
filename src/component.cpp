#include "../headers/component.h"

std::string Component::getLibComponent() const
{
    return libComponent;
}

void Component::setLibComponent(const std::string &newLibComponent)
{
    libComponent = newLibComponent;
}

std::string Component::getLibVariant() const
{
    return libVariant;
}

void Component::setLibVariant(const std::string &newLibVariant)
{
    libVariant = newLibVariant;
}

std::string Component::getValue() const
{
    return value;
}

void Component::setValue(const std::string &newValue)
{
    value = newValue;
}

bool Component::getLockAssembly() const
{
    return lockAssembly;
}

void Component::setLockAssembly(bool newLockAssembly)
{
    lockAssembly = newLockAssembly;
}

std::list<Attribute> Component::getAttributeList() const
{
    return attributeList;
}

void Component::setAttributeList(const std::list<Attribute> &newAttributeList)
{
    attributeList = newAttributeList;
}

std::list<Signal> Component::getSignalList() const
{
    return signalList;
}

void Component::setSignalList(const std::list<Signal> &newSignalList)
{
    signalList = newSignalList;
}

Component::Component() {}

Component::~Component() {}
