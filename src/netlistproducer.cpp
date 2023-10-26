#include "../headers/netlistproducer.h"

#include <regex>

std::string NetlistProducer::getValueOrDefault(std::string string)
{
    return string.empty() ? "-" : string;
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
        std::list<Attribute> attributeList = component.getAttributeList();
        if (attributeList.empty()) {
            result += "-\n";
        } else {
            result += getValueOrDefault((*attributeList.begin()).getValue()) + "\n";
        }
    }
    return result;
}
