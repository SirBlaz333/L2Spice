#include "../headers/netlistproducer.h"
#include "headers/attributeutils.h"

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
        const auto net = pair.second;
        std::string name = net.getName();
        if (name == "GND" || name == "") {
            netOrderMap[net.getUuid()] = 0;
        } else {
            netOrderMap[net.getUuid()] = std::stoi(name.substr(1, name.size() - 1));
        }
    }
    std::string result;
    for (const auto &pair : componentMap) {
        Component component = pair.second;
        if (component.getValue() != "GND") {
            result += component.getName() + " ";
            std::list<Signal> signalList = component.getSignalList();
            for (Signal signal : signalList) {
                std::string uuid = signal.getNet().getUuid();
                result += uuid.empty() ? "-" : std::to_string(netOrderMap[uuid]);
                result += " ";
            }
            result += attribute_utils::createSourceType(component);
            result += "\n";
        }
    }
    return result;
}
