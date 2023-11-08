#include "../headers/netlistproducer.h"
#include "headers/attributeutils.h"

#include <regex>
#include <set>

std::string NetlistProducer::getValueOrDefault(std::string string)
{
    return string.empty() ? "-" : string;
}

NetlistProducer::NetlistProducer() {}

NetlistProducer::~NetlistProducer() {}

std::string writeSignal(std::string uuid, std::map<std::string, int> netOrderMap)
{
    return uuid.empty() ? "-" : std::to_string(netOrderMap[uuid]) + " ";
}

std::string writeComponent(std::string parentSignalUuid,
                           Component component,
                           std::map<std::string, std::list<Component>> netComponentsMap,
                           std::map<std::string, int> netOrderMap,
                           std::set<std::string> *componentSet)
{
    if (componentSet->count(component.getUuid()) != 0 || component.getValue() == "GND") {
        return "";
    }
    componentSet->insert({component.getUuid()});
    std::string result = component.getName() + " ";
    std::list<Signal> signalList = component.getSignalList();
    if(!parentSignalUuid.empty()) {
        result += writeSignal(parentSignalUuid, netOrderMap);
    }
    for (Signal signal : signalList) {
        if(signal.getNet().getUuid() != parentSignalUuid) {
            result += writeSignal(signal.getNet().getUuid(), netOrderMap);
        }
    }
    result += attribute_utils::parseAttributes(component);
    result += "\n";
    for (Signal signal : signalList) {
        if (signal.getNet().getUuid() != parentSignalUuid
            && netOrderMap[signal.getNet().getUuid()] != 0) {
            std::list<Component> componentList = netComponentsMap[signal.getNet().getUuid()];
            for (Component &component : componentList) {
                result += writeComponent(signal.getNet().getUuid(),
                                         component,
                                         netComponentsMap,
                                         netOrderMap,
                                         componentSet);
            }
        }
    }
    return result;
}

std::map<std::string, std::list<Component>> createNetComponentsMap(
    std::map<std::string, Component> componentMap)
{
    std::map<std::string, std::list<Component>> map;
    for (const auto &pair : componentMap) {
        Component component = pair.second;
        std::list<Signal> signalList = component.getSignalList();
        for (Signal signal : signalList) {
            std::list<Component> componentList = map[signal.getNet().getUuid()];
            componentList.push_back(component);
            map[signal.getNet().getUuid()] = componentList;
        }
    }
    return map;
}

Component findComponent(std::string uuid, std::map<std::string, Component> componentMap)
{
    for (const auto &pair : componentMap) {
        Component currentComponent = pair.second;
        for (Signal &signal : currentComponent.getSignalList()) {
            if (signal.getNet().getUuid() == uuid) {
                return currentComponent;
            }
        }
    }
    return Component();
}

std::string NetlistProducer::produceSpiceNotationNetlist(const Circuit &circuit)
{
    Variant variant = circuit.getVariant();
    NetClass netclass = circuit.getNetclass();
    std::map<std::string, Net> netMap = circuit.getNetMap();
    std::map<std::string, Component> componentMap = circuit.getComponentMap();
    std::map<std::string, int> netOrderMap;
    std::map<std::string, std::list<Component>> map = createNetComponentsMap(componentMap);
    std::string uuidWithLowestOrder;
    int lastOrder = INT_MAX;
    for (const auto &pair : netMap) {
        const auto net = pair.second;
        std::string name = net.getName();
        if (name == "GND" || name == "") {
            netOrderMap[net.getUuid()] = 0;
        } else {
            int currentOrder = std::stoi(name.substr(1, name.size() - 1)) * 10;
            netOrderMap[net.getUuid()] = currentOrder;
            if (currentOrder < lastOrder) {
                lastOrder = currentOrder;
                uuidWithLowestOrder = net.getUuid();
            }
        }
    }
    std::string result;
    Component component = findComponent(uuidWithLowestOrder, componentMap);
    std::set<std::string> set;

    return writeComponent("", component, map, netOrderMap, &set);
}
