#include "../headers/device.h"

const Variant *Device::getVariant() const
{
    return variant;
}

void Device::setProperty(const std::string &propertyName, const Element *property)
{
    if (property->getType() == "variant") {
        variant = dynamic_cast<const Variant *>(property);
    }
}

Device::Device()
{
    type = "device";
}

Device::~Device() {}
