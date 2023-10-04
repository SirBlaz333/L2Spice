#ifndef ELEMENT_H
#define ELEMENT_H

#include <headers/ElementIO.h>
#include <string>

class Element
{
private:
    std::string fullname;
    ElementIO io;
    std::string value;

public:
    Element(const std::string &fullname, const ElementIO &io, const std::string &value);
    ~Element();
};

#endif // ELEMENT_H
