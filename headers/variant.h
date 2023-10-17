#ifndef VARIANT_H
#define VARIANT_H

#include "element.h"

class Variant : public Element
{
private:
    std::string description;

public:
    Variant();
    ~Variant();
    std::string getDescription() const;
    void setChildProperty(const std::string &propertyName, const std::string &property);
    void setProperty(const std::string &propertyName, const Element &property);
};

#endif // VARIANT_H
