#ifndef NET_H
#define NET_H

#include "netclass.h"

class Net : public NetClass
{
private:
    bool autoMode;
    NetClass netclass;
public:
    Net();
    ~Net();

    bool getAutoMode() const;
    NetClass getNetclass() const;
    void setChildProperty(const std::string &propertyName, const std::string &property);
    void setProperty(const std::string &propertyName, const Element &property);
};

#endif // NET_H
