#ifndef VARIANT_H
#define VARIANT_H

#include "element.h"

class Variant : Element
{
private:
    std::string description;

public:
    Variant();
    ~Variant();

    std::string getDescription() const;
};

#endif // VARIANT_H
