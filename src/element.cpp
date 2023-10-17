#include "headers/element.h"

std::string Element::getUuid() const
{
    return uuid;
}

std::string Element::getName() const
{
    return name;
}

void Element::setProperty(const std::string &propertyName, const std::string &property)
{
    if (propertyName == "name") {
        name = property;
    } else if (propertyName == "uuid") {
        uuid = property;
    } else {
        setChildProperty(propertyName, property);
    }
}

Element::Element() {}

Element::~Element() {}
