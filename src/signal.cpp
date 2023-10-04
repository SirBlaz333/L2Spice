#include "headers/signal.h"

Signal::Signal(std::string uuid, std::string name)
{
    this->uuid = uuid;
    this->name = name;
}

Signal::~Signal() {}

std::string Signal::getUUID()
{
    return this->getUUID();
}

std::string Signal::getName()
{
    return this->name;
}
