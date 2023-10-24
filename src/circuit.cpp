#include "headers/circuit.h"

Circuit::Circuit(){}

Circuit::~Circuit() {}

void Circuit::setVariant(const Variant &newVariant)
{
    variant = newVariant;
}

void Circuit::setNetclass(const NetClass &newNetclass)
{
    netclass = newNetclass;
}

void Circuit::setNetMap(const std::map<std::string, Net> &newNetMap)
{
    netMap = newNetMap;
}

void Circuit::setComponentMap(const std::map<std::string, Component> &newComponentMap)
{
    componentMap = newComponentMap;
}

Variant Circuit::getVariant() const
{
    return variant;
}

NetClass Circuit::getNetclass() const
{
    return netclass;
}

std::map<std::string, Net> Circuit::getNetMap() const
{
    return netMap;
}

std::map<std::string, Component> Circuit::getComponentMap() const
{
    return componentMap;
}
