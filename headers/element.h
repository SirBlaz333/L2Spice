#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

class Element
{
private:
    std::string uuid;
    std::string name;

protected:
    std::string elementType;
    virtual void setChildProperty(const std::string &propertyName, const std::string &property);

public:
    std::string getUuid() const;
    std::string getName() const;
    std::string getElementType() const;
    void setProperty(const std::string &propertyName, const std::string &property);
    virtual void setProperty(const std::string &propertyName, const Element *property);
};

#endif // ELEMENT_H
