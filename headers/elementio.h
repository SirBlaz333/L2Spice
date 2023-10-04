#ifndef ELEMENTIO_H
#define ELEMENTIO_H

#include <string>

class ElementIO
{
private:
    std::string inputId;
    std::string outputId;

public:
    ElementIO(const std::string &inputId, const std::string &outputId);
    ~ElementIO();

    std::string getInputId() const;
    std::string getOutputId() const;
};

#endif // ELEMENTIO_H
