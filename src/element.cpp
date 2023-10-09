#include "headers/element.h"

Element::Element(const std::string &fullname,
                 const ElementIO &io,
                 const std::vector<Attribute> &attributes)
    : fullname(fullname)
    , io(io)
    , attributes(attributes)
{}

Element::~Element() {}
