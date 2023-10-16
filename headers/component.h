#ifndef COMPONENT_H
#define COMPONENT_H

#include "element.h"
#include "headers/attribute.h"
#include "headers/signal.h"
#include <list>

class Component : Element
{
private:
    std::string libComponent;
    std::string libVariant;
    std::string value;
    bool lockAssembly;
    std::list<Attribute> attributeList;
    std::list<Signal> signalList;

public:
    Component(const std::string &libComponent,
              const std::string &libVariant,
              const std::string &value,
              bool lockAssembly,
              const std::list<Attribute> &attributeList,
              const std::list<Signal> &signalList,
              const std::string &uuid,
              const std::string &name);
    ~Component();
};

#endif // COMPONENT_H
