#ifndef COMPONENT_H
#define COMPONENT_H

#include "element.h"
#include "headers/attribute.h"
#include "headers/signal.h"
#include <list>

class Component : Element
{
private:
    std::string libComponent;
    std::string libVariant;
    std::string value;
    bool lockAssembly;
    std::list<Attribute> attributeList;
    std::list<Signal> signalList;

public:
    Component();
    ~Component();

    std::string getLibComponent() const;
    void setLibComponent(const std::string &newLibComponent);
    std::string getLibVariant() const;
    void setLibVariant(const std::string &newLibVariant);
    std::string getValue() const;
    void setValue(const std::string &newValue);
    bool getLockAssembly() const;
    void setLockAssembly(bool newLockAssembly);
    std::list<Attribute> getAttributeList() const;
    void setAttributeList(const std::list<Attribute> &newAttributeList);
    std::list<Signal> getSignalList() const;
    void setSignalList(const std::list<Signal> &newSignalList);
};

#endif // COMPONENT_H
