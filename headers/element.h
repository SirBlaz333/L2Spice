#ifndef ELEMENT_H
#define ELEMENT_H

#include "attribute.h"

#include <headers/ElementIO.h>
#include <string>
#include <vector>

class Element
{
private:
    std::string fullname;
    ElementIO io;
    std::vector<Attribute> attributes;

public:
    Element(const std::string &fullname, const ElementIO &io, const std::vector<Attribute> &attributes);

    ~Element();
};

#endif // ELEMENT_H
