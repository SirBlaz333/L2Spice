#ifndef VARIANT_H
#define VARIANT_H

#include "element.h"

class Variant : Element
{
private:
    std::string description;

public:
    Variant(const std::string &description, const std::string &uuid, const std::string &name);
    ~Variant();
};

#endif // VARIANT_H
