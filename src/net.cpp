#include "../headers/net.h"

bool Net::getAutoMode() const
{
    return autoMode;
}

NetClass Net::getNetclass() const
{
    return netclass;
}

void Net::setChildProperty(const std::string &propertyName, const std::string &property)
{
    if (propertyName == "auto") {
        autoMode = (property == "true");
    }
}

void Net::setProperty(const std::string &propertyName, const Element &property)
{
    if (propertyName == "netclass") {
        netclass = *((NetClass *) &property);
    }
}

Net::Net()
{
    type = "net";
}

Net::~Net() {}
