#include "headers/element.h"

std::string Element::getUuid() const
{
    return uuid;
}

void Element::setUuid(const std::string &newUuid)
{
    uuid = newUuid;
}

std::string Element::getName() const
{
    return name;
}

void Element::setName(const std::string &newName)
{
    name = newName;
}

Element::Element() {}

Element::~Element() {}
