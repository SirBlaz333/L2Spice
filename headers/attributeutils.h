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

std::string getUnitShortPrefix(std::string unit);
std::string getFullUnitPrefix(std::string shortPrefix);
std::string parseAttributes(Component component, bool includeName);
std::string getUnitWithoutPrefix(std::string unit);
}

#endif // ATTRIBUTEUTILS_H
