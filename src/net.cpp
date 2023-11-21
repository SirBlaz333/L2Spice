#include "../headers/net.h"

bool Net::getAutoMode() const
{
    return autoMode;
}

const NetClass Net::getNetclass() const
{
    return *netclass;
}

void Net::setChildProperty(const QString &propertyName, const QString &property)
{
    if (propertyName == "auto") {
        autoMode = (property == "true");
    }
}

void Net::setProperty(const QString &propertyName, const Element* property)
{
    if (propertyName == "netclass") {
        netclass = dynamic_cast<const NetClass *>(property);
    }
}

Net::Net()
{
    elementType = "net";
}

Net::~Net() {}
