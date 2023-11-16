#include "headers/circuit.h"

Circuit::Circuit(){}

Circuit::~Circuit() {}

void Circuit::addElement(const Element *element)
{
    if (element->getElementType() == "variant") {
        variant = dynamic_cast<const Variant *>(element);
        return;
    }
    if (element->getElementType() == "netclass") {
        netclass = dynamic_cast<const NetClass *>(element);
        return;
    }
    if (element->getElementType() == "net") {
        const Net *net = dynamic_cast<const Net *>(element);
        netMap[net->getUuid()] = *net;
        return;
    }
    if (element->getElementType() == "component") {
        const Component *component = dynamic_cast<const Component *>(element);
        componentMap[component->getUuid()] = *component;
        return;
    }
}

void Circuit::setSubcircuitStatus(bool isSubcircuit, std::string name)
{
    this->isSubcircuit = isSubcircuit;
    this->name = name;
}


bool Circuit::getSubcircuitStatus() const
{
    return isSubcircuit;
}

std::string Circuit::getName() const
{
    return name;
}

const Variant Circuit::getVariant() const
{
    return *variant;
}

const NetClass Circuit::getNetclass() const
{
    return *netclass;
}

std::map<std::string, Net> Circuit::getNetMap() const
{
    return netMap;
}

std::map<std::string, Component> Circuit::getComponentMap() const
{
    return componentMap;
}
