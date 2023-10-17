#include "../headers/variant.h"

std::string Variant::getDescription() const
{
    return description;
}

void Variant::setChildProperty(const std::string &propertyName, const std::string &property)
{
    if (propertyName == "description") {
        description = property;
    }
}

void Variant::setProperty(const std::string &propertyName, const Element &property) {}

Variant::Variant() {}

Variant::~Variant() {}
