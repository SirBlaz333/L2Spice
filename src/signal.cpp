#include "headers/signal.h"

std::string Signal::getUuid() const
{
    return uuid;
}

std::string Signal::getNetUuid() const
{
    return netUuid;
}

void Signal::setUuid(const std::string &newUuid)
{
    uuid = newUuid;
}

void Signal::setNetUuid(const std::string &newNetUuid)
{
    netUuid = newNetUuid;
}

Signal::Signal() {}

Signal::~Signal() {}
