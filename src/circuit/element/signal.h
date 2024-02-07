#ifndef SIGNAL_H
#define SIGNAL_H

#include "element.h"
#include "net.h"

class Signal : public Element
{
private:
    const Net* net;
    void setProperty(const QString &propertyName, const Element* property);

public:
    Signal();
    virtual ~Signal();
    const Net getNet() const;

};

#endif // SIGNAL_H
