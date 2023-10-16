#include "../headers/attribute.h"

Attribute::Attribute(const std::string &name,
                     const std::string &type,
                     const std::string &unit,
                     double value)
    : name(name)
    , type(type)
    , unit(unit)
    , value(value)
{}

Attribute::~Attribute() {}
