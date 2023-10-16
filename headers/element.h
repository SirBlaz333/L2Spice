#ifndef ELEMENT_H
#define ELEMENT_H

#include <headers/ElementIO.h>
#include <string>
#include <vector>

class Element
{
private:
    std::string uuid;
    std::string name;
public:
    Element(const std::string &uuid, const std::string &name);
    ~Element();
};

#endif // ELEMENT_H
