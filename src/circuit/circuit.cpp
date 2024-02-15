#include "circuit.h"

Circuit::Circuit() {}

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
        nets.append(*net);
        return;
    }
    if (element->getElementType() == "component") {
        const Component *component = dynamic_cast<const Component *>(element);
        components.append(*component);
        return;
    }
    if (element->getElementType() == "model") {
        const Component *component = dynamic_cast<const Component *>(element);
        models.append(*component);
        return;
    }
    if (element->getElementType() == "tran") {
        tran = dynamic_cast<const Component *>(element);
        return;
    }
    if (element->getElementType() == "probe" || element->getElementType() == "meter") {
        const Component *component = dynamic_cast<const Component *>(element);
        outputs.append(*component);
        return;
    }
    if (element->getElementType() == "text") {
        const Component *component = dynamic_cast<const Component *>(element);
        texts.append(*component);
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

const Component Circuit::getTran() const
{
    if (tran == nullptr) {
        return Component();
    }
    return *tran;
}

QList<Net> Circuit::getNets() const
{
    return nets;
}

QList<Component> Circuit::getComponents() const
{
    return components;
}

QList<Component> Circuit::getModels() const
{
    return models;
}

QList<Component> Circuit::getOutputs() const
{
    return outputs;
}

QList<Component> Circuit::getTexts() const
{
    return texts;
}
