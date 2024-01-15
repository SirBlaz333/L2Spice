#include "element.h"

QString Element::getUuid() const
{
    return uuid;
}

QString Element::getName() const
{
    return name;
}

QString Element::getElementType() const
{
    return elementType;
}

void Element::setProperty(const QString &propertyName, const QString &property)
{
    if (propertyName == "name") {
        name = property;
    } else if (propertyName == "uuid") {
        uuid = property;
    } else {
        setChildProperty(propertyName, property);
    }
}

void Element::setProperty(const QString &propertyName, const Element *property) {}

void Element::setChildProperty(const QString &propertyName, const QString &property) {}
