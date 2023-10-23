#ifndef VARIANT_H
#define VARIANT_H

#include "element.h"

class Variant : public Element
{
private:
    std::string description;
    void setChildProperty(const std::string &propertyName, const std::string &property);

public:
    Variant();
    ~Variant();
    std::string getDescription() const;

};

#endif // VARIANT_H
