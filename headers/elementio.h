#ifndef ELEMENTIO_H
#define ELEMENTIO_H

#include <string>

class ElementIO
{
private:
    std::string input_id;
    std::string output_id;
public:
    ElementIO();
    ElementIO(std::string input_id, std::string output_id);
    ~ElementIO();
    std::string getInputID();
    std::string getOutputID();
};

#endif // ELEMENTIO_H
