#include "../headers/net.h"

bool Net::getAutoMode() const
{
    return autoMode;
}

void Net::setAutoMode(bool newAutoMode)
{
    autoMode = newAutoMode;
}

NetClass Net::getNetclass() const
{
    return netclass;
}

void Net::setNetclass(const NetClass &newNetclass)
{
    netclass = newNetclass;
}

Net::Net() {}

Net::~Net() {}
