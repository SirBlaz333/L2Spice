#ifndef SIGNAL_H
#define SIGNAL_H

#include "element.h"
#include "net.h"

#include <string>

class Signal : public Element
{
private:
    const Net* net;
    void setProperty(const QString &propertyName, const Element* property);

public:
    Signal();
    ~Signal();
    const Net getNet();

};

#endif // SIGNAL_H
