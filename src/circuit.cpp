#include "headers/circuit.h"

Circuit::~Circuit() {}

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

Circuit::Circuit(const Variant &variant,
                 const NetClass &netclass,
                 const std::map<std::string, Net> &netMap,
                 const std::map<std::string, Component> &componentMap)
    : variant(variant)
    , netclass(netclass)
    , netMap(netMap)
    , componentMap(componentMap)
{}
