#include <headers/elementio.h>

ElementIO::ElementIO(const std::string &inputId, const std::string &outputId) : inputId(inputId),
    outputId(outputId)
{}

ElementIO::~ElementIO() {}

std::string ElementIO::getInputId() const
{
    return inputId;
}

std::string ElementIO::getOutputId() const
{
    return outputId;
}
