#include "headers/circuit.h"

std::string Circuit::getUuid() const
{
    return uuid;
}

std::string Circuit::getName() const
{
    return name;
}

std::vector<Signal> Circuit::getSignalVector() const
{
    return signalVector;
}

std::vector<Element> Circuit::getElementVector() const
{
    return elementVector;
}

Circuit::Circuit(const std::string &uuid,
                 const std::string &name,
                 const std::vector<Signal> &signalVector,
                 const std::vector<Element> &elementVector)
    : uuid(uuid)
    , name(name)
    , signalVector(signalVector)
    , elementVector(elementVector)
{}

Circuit::~Circuit() {}
