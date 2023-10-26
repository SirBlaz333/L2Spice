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

std::string parseAttributes(Attribute sourceType, std::list<Attribute> attributeList)
{
    std::string result = sourceType.getValue();
    result += "(";
    for (const auto &attribute : attributeList) {
        if (attribute.getName() != "SOURCETYPE" && !attribute.getValue().empty()) {
            result += attribute.getValue() + " ";
        }
    }
    result.pop_back();
    return result + ")";
}

std::string attribute_utils::createSourceType(Component component)
{
    for (const auto &attribute : component.getAttributeList()) {
        if (attribute.getName() == "SOURCETYPE") {
            return parseAttributes(attribute, component.getAttributeList());
        }
    }
    return "";
}
