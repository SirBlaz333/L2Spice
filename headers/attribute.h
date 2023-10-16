#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>

class Attribute
{
private:
    std::string name;
    std::string type;
    std::string unit;
    double value;
public:
    Attribute(const std::string &name, const std::string &type, const std::string &unit, double value);
    ~Attribute();
};

#endif // ATTRIBUTE_H
