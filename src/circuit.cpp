#include "headers/circuit.h"

Circuit::Circuit(){}

Circuit::~Circuit() {}

void Circuit::addElement(const Element *element)
{
    if (element->getType() == "variant") {
        variant = dynamic_cast<const Variant *>(element);
        return;
    }
    if (element->getType() == "netclass") {
        netclass = dynamic_cast<const NetClass *>(element);
        return;
    }
    if (element->getType() == "net") {
        const Net *net = dynamic_cast<const Net *>(element);
        netMap[net->getUuid()] = *net;
        return;
    }
    if (element->getType() == "component") {
        const Component *component = dynamic_cast<const Component *>(element);
        componentMap[component->getUuid()] = *component;
        return;
    }
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
