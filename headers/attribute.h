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

    void setChildProperty(const std::string &propertyName, const std::string &property);

public:
    Attribute();
    ~Attribute();

    std::string getType() const;
    std::string getUnit() const;
    std::string getValue() const;
};

#endif // ATTRIBUTE_H
