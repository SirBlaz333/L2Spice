#ifndef NET_H
#define NET_H

#include "netclass.h"

class Net : NetClass
{
private:
    bool autoMode;
    NetClass netclass;
public:
    Net(bool autoMode, const NetClass &netclass, const std::string &uuid, const std::string &name);
    ~Net();
};

#endif // NET_H
