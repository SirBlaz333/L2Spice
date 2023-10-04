#include "headers/element.h"

Element::Element(std::string fullname, ElementIO io, std::string value)
{
    this->full_name = fullname;
    this->io = io;
    this->value = value;
}

Element::~Element()
{

}
