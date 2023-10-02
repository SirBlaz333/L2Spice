#ifndef ELEMENT_H
#define ELEMENT_H

#include <ElementIO.h>
#include <string>

class Element
{
private:
    std::string full_name;
    ElementIO io;
    std::string value;
public:
    Element(std::string fullname, ElementIO io, std::string value);
};

#endif // ELEMENT_H
