#include "headers/signal.h"

const Net Signal::getNet()
{
    return *net;
}

void Signal::setProperty(const QString &propertyName, const Element *property)
{
    if (propertyName == "net") {
        net = dynamic_cast<const Net *>(property);
    }
}

Signal::Signal()
{
    elementType = "signal";
}

Signal::~Signal() {}
