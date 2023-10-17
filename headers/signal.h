#ifndef SIGNAL_H
#define SIGNAL_H

#include "element.h"
#include "net.h"

#include <string>

class Signal : public Element
{
private:
    Net net;

public:
    Signal();
    ~Signal();
    Net getNet() const;
    void setChildProperty(const std::string &propertyName, const std::string &property);
    void setProperty(const std::string &propertyName, const Element &property);
};

#endif // SIGNAL_H
