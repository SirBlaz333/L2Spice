#ifndef NETCLASS_H
#define NETCLASS_H

#include "element.h"

class NetClass : public Element
{
public:
    NetClass();
    ~NetClass();
    void setChildProperty(const std::string &propertyName, const std::string &property);
    void setProperty(const std::string &propertyName, const Element &property);
};

#endif // NETCLASS_H
