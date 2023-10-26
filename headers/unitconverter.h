#ifndef UNITCONVERTER_H
#define UNITCONVERTER_H

#include <map>
#include <string>


namespace units {
static std::map<std::string, std::string> prefixes = {{"pico", "p"},
                                                      {"nano", "n"},
                                                      {"micro", "u"},
                                                      {"milli", "m"},
                                                      {"kilo", "k"},
                                                      {"mega", "meg"}};
std::string getPrefix(std::string unit);
}

#endif // UNITCONVERTER_H
