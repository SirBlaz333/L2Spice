#include "../headers/attributeutils.h"

std::string attribute_utils::getUnitPrefix(std::string unit)
{
    for (const auto &pair : prefixes) {
        if (unit.find(pair.first) != std::string::npos) {
            return pair.second;
        }
    }
    return "";
}

std::string getValueFromAttribute(Attribute attribute)
{
    return attribute.getValue() + attribute_utils::getUnitPrefix(attribute.getUnit()) + " ";
}

std::string parseAttributes(std::list<Attribute>::iterator begin, std::list<Attribute>::iterator end)
{
    std::string result;
    while (begin != end) {
        if (!begin->getValue().empty()) {
            result += getValueFromAttribute(*begin);
        }
        begin++;
    }
    if (!result.empty()) {
        result.pop_back();
    }
    return result;
}

std::string attribute_utils::parseAttributes(Component component)
{
    std::list<Attribute> attributes = component.getAttributeList();
    std::list<Attribute>::iterator begin = attributes.begin();
    std::list<Attribute>::iterator end = attributes.end();
    if (begin->getName() == "SOURCETYPE") {
        std::string result = begin->getValue() + "(";
        return result + parseAttributes(++begin, end) + ")";
    }
    return parseAttributes(begin, end);
}
