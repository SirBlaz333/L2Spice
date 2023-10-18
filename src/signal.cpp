#include "headers/signal.h"

Net Signal::getNet() const
{
    return net;
}

void Signal::setProperty(const std::string &propertyName, const Element &property)
{
    if (propertyName == "net") {
        net = *((Net *) &property);
    }
}

Signal::Signal()
{
    type = "signal";
}

Signal::~Signal() {}
