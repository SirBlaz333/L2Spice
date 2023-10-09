#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "headers/attributetype.h"
#include <string>

class Attribute
{
private:
    std::string name;
    AttributeType type;
    std::string unit;
    double value;
public:
    Attribute();
};

#endif // ATTRIBUTE_H
