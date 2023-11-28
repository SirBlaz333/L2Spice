#include "device.h"

const Variant *Device::getVariant() const
{
    return variant;
}

void Device::setProperty(const QString &propertyName, const Element *property)
{
    if (property->getElementType() == "variant") {
        variant = dynamic_cast<const Variant *>(property);
    }
}

Device::Device()
{
    elementType = "device";
}

Device::~Device() {}
