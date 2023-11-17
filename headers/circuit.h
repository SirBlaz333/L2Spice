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
    bool isSubcircuit;
    std::string name;
    const Variant* variant;
    const NetClass* netclass;
    const Component* tran = nullptr;
    std::map<std::string, Net> netMap;
    std::map<std::string, Component> componentMap;
    std::map<std::string, Component> modelMap;

public:
    Circuit();
    ~Circuit();
    const Variant getVariant() const;
    const NetClass getNetclass() const;
    const Component getTran() const;
    std::map<std::string, Net> getNetMap() const;
    std::map<std::string, Component> getComponentMap() const;
    std::map<std::string, Component> getModelMap() const;
    void addElement(const Element *element);
    void setSubcircuitStatus(bool isSubcircuit, std::string name);
    bool getSubcircuitStatus() const;
    std::string getName() const;
};

#endif // CIRCUIT_H
