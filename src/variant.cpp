#include "../headers/variant.h"

std::string Variant::getDescription() const
{
    return description;
}

void Variant::setDescription(const std::string &newDescription)
{
    description = newDescription;
}

Variant::Variant() {}

Variant::~Variant() {}
