#ifndef DEVICE_H
#define DEVICE_H

#include "element.h"
#include "variant.h"


class Device : public Element
{
private:
    const Variant *variant;
    void setProperty(const std::string &propertyName, const Element *property);

public:
    Device();
    ~Device();
    const Variant *getVariant() const;

};

#endif // DEVICE_H
