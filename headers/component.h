#ifndef COMPONENT_H
#define COMPONENT_H

#include "element.h"
#include "headers/attribute.h"
#include "headers/signal.h"
#include <list>

class Component : public Element
{
private:
    std::string libComponent;
    std::string libVariant;
    std::string value;
    bool lockAssembly;
    std::list<Attribute> attributeList;
    std::list<Signal> signalList;
    void setChildProperty(const std::string &propertyName, const std::string &property);

public:
    Component();
    ~Component();

    std::string getLibComponent() const;
    std::string getLibVariant() const;
    std::string getValue() const;
    bool getLockAssembly() const;
    std::list<Attribute> getAttributeList() const;
    std::list<Signal> getSignalList() const;
    void setProperty(const std::string &propertyName, const Element* property);
};

#endif // COMPONENT_H
