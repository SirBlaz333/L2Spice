#include "../headers/netlistproducer.h"

#include <regex>

std::string NetlistProducer::getValueOrDefault(std::string string)
{
    return string.empty() ? "-" : string;
}

std::string NetlistProducer::createSourceType(std::string name, std::list<Attribute> attributeList)
{
    if (attributeList.empty()) {
        return "";
    }
    std::map<std::string, std::string> map = {{"SIN", "sin"},
                                              {"PWL", "pwl"},
                                              {"PULSE", "pulse"},
                                              {"CUSTOM", "cus"},
                                              {"DC", "dc"},
                                              {"NOISE", "noise"},
                                              {"RELAX", "exp"}};

    for (const auto &pair : map) {
        if (name.find(pair.first) != std::string::npos) {
            std::string result = pair.second + "(";
            for (const Attribute &attribute : attributeList) {
                result += getValueOrDefault(attribute.getValue()) + attribute.getUnit();
                if (attribute.getUuid() != attributeList.back().getUuid()) {
                    result += " ";
                }
            }
            result += ")";
            return result;
        }
    }

    Attribute attribute = (*attributeList.begin());
    return getValueOrDefault(attribute.getValue()) + attribute.getUnit();
}

NetlistProducer::NetlistProducer() {}

NetlistProducer::~NetlistProducer() {}

std::string NetlistProducer::produceSpiceNotationNetlist(const Circuit &circuit)
{
    Variant variant = circuit.getVariant();
    NetClass netclass = circuit.getNetclass();
    std::map<std::string, Net> netMap = circuit.getNetMap();
    std::map<std::string, Component> componentMap = circuit.getComponentMap();
    std::map<std::string, int> netOrderMap;
    std::map<std::string, Component> updatedComponentsMap;
    int i = 0;
    for (const auto &pair : netMap) {
        netOrderMap[pair.second.getUuid()] = i++;
    }
    std::string result;
    for (const auto &pair : componentMap) {
        Component component = pair.second;
        result += component.getName() + " ";
        std::list<Signal> signalList = component.getSignalList();
        for (Signal signal : signalList) {
            try {
                int id = netOrderMap.at(signal.getNet().getUuid());
                result += std::to_string(id) + " ";
            } catch (...) {
                result += "- ";
            }
        }
        result += createSourceType(component.getName(), component.getAttributeList());
        result += "\n";
    }
    return result;
}
