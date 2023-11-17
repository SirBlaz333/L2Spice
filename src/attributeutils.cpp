#include "../headers/attributeutils.h"

std::string attribute_utils::getUnitShortPrefix(std::string unit)
{
    for (const auto &pair : prefixes) {
        if (unit.find(pair.first) != std::string::npos) {
            return pair.second;
        }
    }
    return "";
}

std::string attribute_utils::getFullUnitPrefix(std::string shortPrefix)
{
    for (const auto &pair : prefixes) {
        if (shortPrefix == pair.second) {
            return pair.first;
        }
    }
    return "";
}

std::string writeAttribute(Attribute attribute, bool includeName)
{
    std::string result = includeName ? attribute.getName() + "=" : "";
    return result + attribute.getValue() + attribute_utils::getUnitShortPrefix(attribute.getUnit()) + " ";
}

std::string parseAttributes(std::list<Attribute>::iterator begin, std::list<Attribute>::iterator end, bool includeName)
{
    std::string result;
    while (begin != end) {
        if (!begin->getValue().empty()) {
            result += writeAttribute(*begin, includeName);
        }
        begin++;
    }
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}

std::string attribute_utils::parseAttributes(Component component, bool includeName)
{
    std::list<Attribute> attributes = component.getAttributeList();
    std::list<Attribute>::iterator begin = attributes.begin();
    std::list<Attribute>::iterator end = attributes.end();
    if (begin->getName() == "SOURCETYPE") {
        std::string result = begin->getValue() + "(";
        return result + parseAttributes(++begin, end, includeName) + ")";
    }
    return parseAttributes(begin, end, includeName);
}

std::string attribute_utils::getUnitWithoutPrefix(std::string unit)
{
    for (const auto &pair : prefixes) {
        if (unit.find(pair.first) != std::string::npos) {
            return unit.erase(0, pair.first.length());
        }
    }
    return unit;
}
