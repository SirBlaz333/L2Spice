#include "../headers/unitconverter.h"

std::string units::getPrefix(std::string unit)
{
    for (const auto &pair : prefixes) {
        if (unit.find(pair.first) != std::string::npos) {
            return pair.second;
        }
    }
    return "";
}
