#include "../headers/component.h"

Component::Component(const std::string &libComponent,
                     const std::string &libVariant,
                     const std::string &value,
                     bool lockAssembly,
                     const std::list<Attribute> &attributeList,
                     const std::list<Signal> &signalList,
                     const std::string &uuid,
                     const std::string &name)
    : Element(uuid, name)
    , libComponent(libComponent)
    , libVariant(libVariant)
    , value(value)
    , lockAssembly(lockAssembly)
    , attributeList(attributeList)
    , signalList(signalList)
{}

Component::~Component() {}
