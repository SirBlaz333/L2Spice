#include "../headers/variant.h"

Variant::Variant(const std::string &description, const std::string &uuid, const std::string &name)
    : Element(uuid, name)
    , description(description)
{}

Variant::~Variant() {}
