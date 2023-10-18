#ifndef SIGNAL_H
#define SIGNAL_H

#include "element.h"
#include "net.h"

#include <string>

class Signal : public Element
{
private:
    Net net;
    void setProperty(const std::string &propertyName, const Element &property);

public:
    Signal();
    ~Signal();
    Net getNet() const;
};

#endif // SIGNAL_H
