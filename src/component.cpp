#include "../headers/component.h"

Component::Component(const std::string &libComponent,
                     const std::string &libVariant,
                     const std::string &value,
                     bool lockAssembly,
                     const std::vector<Attribute> &attributeVector,
                     const std::vector<Signal> &signalVector,
                     const std::string &uuid,
                     const std::string &name)
    : Element(uuid, name)
    , libComponent(libComponent)
    , libVariant(libVariant)
    , value(value)
    , lockAssembly(lockAssembly)
    , attributeVector(attributeVector)
    , signalVector(signalVector)
{}

Component::~Component() {}
