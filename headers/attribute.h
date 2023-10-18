#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "element.h"

#include <string>

class Attribute : public Element
{
private:
    std::string type;
    std::string unit;
    std::string value;
public:
    Attribute();
    ~Attribute();
    void setChildProperty(const std::string &propertyName, const std::string &property);
};

#endif // ATTRIBUTE_H
