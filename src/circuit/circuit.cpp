#include "circuit.h"

Circuit::Circuit(){}

Circuit::~Circuit() {}

bool Circuit::isEmpty() const
{
    return empty;
}

void Circuit::addElement(const Element *element)
{
    empty = false;
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
    if (element->getElementType() == "model") {
        const Component *component = dynamic_cast<const Component *>(element);
        modelMap[component->getUuid()] = *component;
        return;
    }
    if (element->getElementType() == "tran") {
        tran = dynamic_cast<const Component *>(element);
        return;
    }
}

void Circuit::setSubcircuitStatus(bool isSubcircuit, QString name)
{
    this->isSubcircuit = isSubcircuit;
    this->name = name == "" ? "DEFAULT" : name;
}


bool Circuit::getSubcircuitStatus() const
{
    return isSubcircuit;
}

QString Circuit::getName() const
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

const Component Circuit::getTran() const
{
    if (tran == nullptr) {
        return Component();
    }
    return *tran;
}

QMap<QString, Net> Circuit::getNetMap() const
{
    return netMap;
}

QMap<QString, Component> Circuit::getComponentMap() const
{
    return componentMap;
}

QMap<QString, Component> Circuit::getModelMap() const
{
    return modelMap;
}
