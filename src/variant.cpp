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

Variant::Variant()
{
    type = "variant";
}

Variant::~Variant() {}
