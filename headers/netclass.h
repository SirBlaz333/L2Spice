#ifndef NETCLASS_H
#define NETCLASS_H

#include "element.h"

class NetClass : Element
{
public:
    NetClass(const std::string &uuid, const std::string &name);
    ~NetClass();
};

#endif // NETCLASS_H
