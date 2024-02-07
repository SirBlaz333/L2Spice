#ifndef NET_H
#define NET_H

#include "netclass.h"

class Net : public NetClass
{
private:
    bool autoMode;
    const NetClass* netclass;
    void setChildProperty(const QString &propertyName, const QString &property);
public:
    Net();
    virtual ~Net();

    bool getAutoMode() const;
    const NetClass getNetclass() const;
    void setProperty(const QString &propertyName, const Element* property);
};

#endif // NET_H
