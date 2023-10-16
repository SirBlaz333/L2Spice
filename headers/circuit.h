#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "component.h"
#include "net.h"
#include "variant.h"
#include <map>
#include <string>

class Circuit
{
private:
    Variant variant;
    NetClass netclass;
    std::map<std::string, Net> netMap;
    std::map<std::string, Component> componentMap;

public:
    Circuit(const Variant &variant,
            const NetClass &netclass,
            const std::map<std::string, Net> &netMap,
            const std::map<std::string, Component> &componentMap);
    ~Circuit();
    Variant getVariant() const;
    NetClass getNetclass() const;
    std::map<std::string, Net> getNetMap() const;
    std::map<std::string, Component> getComponentMap() const;
};

#endif // CIRCUIT_H
