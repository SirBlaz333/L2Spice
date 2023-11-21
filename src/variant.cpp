#include "../headers/variant.h"

QString Variant::getDescription() const
{
    return description;
}

void Variant::setChildProperty(const QString &propertyName, const QString &property)
{
    if (propertyName == "description") {
        description = property;
    }
}

Variant::Variant()
{
    elementType = "variant";
}

Variant::~Variant() {}
