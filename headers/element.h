#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

class Element
{
private:
    std::string uuid;
    std::string name;

protected:
    void setChildProperty(const std::string &propertyName, const std::string &property);
public:
    Element();
    ~Element();

    std::string getUuid() const;
    std::string getName() const;
    void setProperty(const std::string &propertyName, const std::string &property);
    void setProperty(const std::string &propertyName, const Element &property);
};

#endif // ELEMENT_H
