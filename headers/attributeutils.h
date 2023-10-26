#ifndef ATTRIBUTEUTILS_H
#define ATTRIBUTEUTILS_H

#include "component.h"

#include <list>
#include <map>
#include <string>


namespace attribute_utils {
static std::map<std::string, std::string> prefixes = {{"pico", "p"},
                                                      {"nano", "n"},
                                                      {"micro", "u"},
                                                      {"milli", "m"},
                                                      {"kilo", "k"},
                                                      {"mega", "meg"}};

std::string getUnitPrefix(std::string unit);
std::string createSourceType(Component component);
}

#endif // ATTRIBUTEUTILS_H
