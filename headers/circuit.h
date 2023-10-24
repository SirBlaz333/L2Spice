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
    Circuit();
    ~Circuit();
    Variant getVariant() const;
    NetClass getNetclass() const;
    std::map<std::string, Net> getNetMap() const;
    std::map<std::string, Component> getComponentMap() const;

    void setVariant(const Variant &newVariant);
    void setNetclass(const NetClass &newNetclass);
    void setNetMap(const std::map<std::string, Net> &newNetMap);
    void setComponentMap(const std::map<std::string, Component> &newComponentMap);
};

#endif // CIRCUIT_H
