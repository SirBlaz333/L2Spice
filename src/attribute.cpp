#include "../headers/attribute.h"

Attribute::Attribute()
{
    elementType = "attribute";
}

Attribute::~Attribute() {}

std::string Attribute::getType() const
{
    return type;
}

std::string Attribute::getUnit() const
{
    return unit;
}

std::string Attribute::getValue() const
{
    return value;
}

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
