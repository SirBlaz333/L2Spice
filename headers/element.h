#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

class Element
{
private:
    std::string uuid;
    std::string name;

protected:
    virtual void setChildProperty(const std::string &propertyName, const std::string &property) = 0;
public:
    Element();
    ~Element();

    std::string getUuid() const;
    std::string getName() const;
    void setProperty(const std::string &propertyName, const std::string &property);
    virtual void setProperty(const std::string &propertyName, const Element &property) = 0;
};

#endif // ELEMENT_H
