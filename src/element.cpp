#include "headers/element.h"

Element::Element(const std::string &fullname, const ElementIO &io, const std::string &value)
    : fullname(fullname)
    , io(io)
    , value(value)
{}

Element::~Element() {}
