#include <headers/elementio.h>

ElementIO::ElementIO()
{
    this->input_id = "";
    this->output_id = "";
}

ElementIO::ElementIO(std::string input_id, std::string output_id)
{
    this->input_id = input_id;
    this->output_id = output_id;
}

std::string ElementIO::getInputID()
{
    return this->input_id;
}

std::string ElementIO::getOutputID()
{
    return this->output_id;
}
