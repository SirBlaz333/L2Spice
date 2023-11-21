#include "../headers/attribute.h"

Attribute::Attribute()
{
    elementType = "attribute";
}

Attribute::~Attribute() {}

QString Attribute::getType() const
{
    return type;
}

QString Attribute::getUnit() const
{
    return unit;
}

QString Attribute::getValue() const
{
    return value;
}

void Attribute::setChildProperty(const QString &propertyName, const QString &property)
{
    if (propertyName == "type") {
        type = property;
    } else if (propertyName == "unit") {
        unit = property;
    } else if (propertyName == "value") {
        value = property;
    }
}
