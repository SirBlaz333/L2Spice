#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "headers/element.h"
#include "headers/signal.h"
#include <string>
#include <vector>

class Circuit
{
private:
    std::string uuid;
    std::string name;
    std::vector<Signal> signalVector;
    std::vector<Element> elementVector;

public:
    Circuit(const std::string &uuid,
            const std::string &name,
            const std::vector<Signal> &signalVector,
            const std::vector<Element> &elementVector);
    ~Circuit();
    std::string getUuid() const;
    std::string getName() const;
    std::vector<Signal> getSignalVector() const;
    std::vector<Element> getElementVector() const;
};

#endif // CIRCUIT_H
