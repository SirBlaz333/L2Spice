#ifndef NET_H
#define NET_H

#include "netclass.h"

class Net : NetClass
{
private:
    bool autoMode;
    NetClass netclass;
public:
    Net();
    ~Net();

    bool getAutoMode() const;
    void setAutoMode(bool newAutoMode);
    NetClass getNetclass() const;
    void setNetclass(const NetClass &newNetclass);
};

#endif // NET_H
