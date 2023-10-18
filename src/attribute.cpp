#include "../headers/attribute.h"

Attribute::Attribute() {}

Attribute::~Attribute() {}

void Attribute::setChildProperty(const std::string &propertyName, const std::string &property)
{
    if (propertyName == "type") {
        type = property;
    } else if (propertyName == "unit") {
        unit = property;
    } else if (propertyName == "value") {
        value = property;
    }
}
