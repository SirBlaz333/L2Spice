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
    void setDescription(const std::string &newDescription);
};

#endif // VARIANT_H
