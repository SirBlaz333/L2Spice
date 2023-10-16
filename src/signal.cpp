#include "headers/signal.h"

std::string Signal::getUuid() const
{
    return uuid;
}

std::string Signal::getNetUuid() const
{
    return netUuid;
}

Signal::Signal(const std::string &uuid, const std::string &netUuid)
    : uuid(uuid)
    , netUuid(netUuid)
{}

Signal::~Signal() {}
