#ifndef COMPONENT_H
#define COMPONENT_H

#include "element.h"
#include "headers/attribute.h"
#include "headers/signal.h"

class Component : Element
{
private:
    std::string libComponent;
    std::string libVariant;
    std::string value;
    bool lockAssembly;
    std::vector<Attribute> attributeVector;
    std::vector<Signal> signalVector;

public:
    Component(const std::string &libComponent,
              const std::string &libVariant,
              const std::string &value,
              bool lockAssembly,
              const std::vector<Attribute> &attributeVector,
              const std::vector<Signal> &signalVector,
              const std::string &uuid,
              const std::string &name);
    ~Component();
};

#endif // COMPONENT_H
