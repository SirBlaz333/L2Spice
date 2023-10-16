#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

class Element
{
private:
    std::string uuid;
    std::string name;
public:
    Element();
    ~Element();

    std::string getUuid() const;
    void setUuid(const std::string &newUuid);
    std::string getName() const;
    void setName(const std::string &newName);
};

#endif // ELEMENT_H
