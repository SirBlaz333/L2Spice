#include "../headers/netlistproducer.h"
#include "headers/attributeutils.h"

#include <QMap>
#include <QSet>
#include <regex>
#include <set>

QString NetlistProducer::getValueOrDefault(QString string)
{
    return string.isEmpty() ? "-" : string;
}

NetlistProducer::NetlistProducer() {}

NetlistProducer::~NetlistProducer() {}

QString writeSignal(QString uuid, QMap<QString, int> netOrderMap)
{
    return uuid.isEmpty() ? "-" : QString::number(netOrderMap[uuid]) + " ";
}

QString writeComponent(QString parentSignalUuid,
                           Component component,
                           QMap<QString, QList<Component>> netComponentsMap,
                           QMap<QString, int> netOrderMap,
                           QSet<QString> *repeats,
                           bool includeAttributeName)
{
    if (repeats->contains(component.getUuid()) || component.getValue() == "GND") {
        return "";
    }
    repeats->insert({component.getUuid()});
    QString result = component.getName() + " ";
    QList<Signal> signalList = component.getSignalList();
    if(!parentSignalUuid.isEmpty()) {
        result += writeSignal(parentSignalUuid, netOrderMap);
    }
    for (Signal signal : signalList) {
        if(signal.getNet().getUuid() != parentSignalUuid) {
            result += writeSignal(signal.getNet().getUuid(), netOrderMap);
        }
    }
    result += attribute_utils::parseAttributes(component, includeAttributeName);
    result += "\n";
    for (Signal signal : signalList) {
        if (signal.getNet().getUuid() != parentSignalUuid
            && netOrderMap[signal.getNet().getUuid()] != 0) {
            QList<Component> componentList = netComponentsMap[signal.getNet().getUuid()];
            for (Component &component : componentList) {
                result += writeComponent(signal.getNet().getUuid(),
                                         component,
                                         netComponentsMap,
                                         netOrderMap,
                                         repeats,
                                         includeAttributeName);
            }
        }
    }
    return result;
}

QMap<QString, QList<Component>> createNetComponentsMap(QMap<QString, Component> componentMap)
{
    QMap<QString, QList<Component>> map;
    for (const auto &component : componentMap) {
        QList<Signal> signalList = component.getSignalList();
        for (Signal signal : signalList) {
            QList<Component> componentList = map[signal.getNet().getUuid()];
            componentList.push_back(component);
            map[signal.getNet().getUuid()] = componentList;
        }
    }
    return map;
}

Component findComponent(QString uuid, QMap<QString, Component> componentMap)
{
    for (const auto &component: componentMap) {
        for (Signal &signal : component.getSignalList()) {
            if (signal.getNet().getUuid() == uuid) {
                return component;
            }
        }
    }
    return Component();
}

QString createSubcircuit(QMap<QString, int> netOrderMap,
                         QMap<QString, QList<Component>> netComponentsMap)
{
    QList<int> inOutList;
    for (auto const &key : netComponentsMap.keys()) {
        QList<Component> components = netComponentsMap[key];
        if (components.size() == 1) {
            inOutList.push_back(netOrderMap[key]);
        }
    }
    std::sort(inOutList.begin(), inOutList.end());
    QString result;
    for (int signalNumber : inOutList) {
        result += std::to_string(signalNumber) + " ";
    }
    result.chop(1);
    return result;
}

QString NetlistProducer::produceSpiceNotationNetlist(const Circuit &circuit)
{
    Variant variant = circuit.getVariant();
    NetClass netclass = circuit.getNetclass();
    QMap<QString, Net> netMap = circuit.getNetMap();
    QMap<QString, Component> componentMap = circuit.getComponentMap();
    QMap<QString, int> netOrderMap;
    QMap<QString, QList<Component>> netComponentsMap = createNetComponentsMap(componentMap);
    QString uuidWithLowestOrder;
    int lastOrder = INT_MAX;
    for (const auto &net : netMap) {
        QString name = net.getName();
        if (name == "GND" || name == "") {
            netOrderMap.insert(net.getUuid(), 0);
        } else {
            int currentOrder = name.mid(1, name.size() - 1).toInt() * 10;
            netOrderMap[net.getUuid()] = currentOrder;
            if (currentOrder < lastOrder) {
                lastOrder = currentOrder;
                uuidWithLowestOrder = net.getUuid();
            }
        }
    }
    Component component = findComponent(uuidWithLowestOrder, componentMap);
    QSet<QString> repeats;
    QString result = writeComponent("", component, netComponentsMap, netOrderMap, &repeats, false);
    if (!circuit.getModelMap().empty()) {
        result += "\n";
    }
    for (const auto &model : circuit.getModelMap()) {
        result += ".MODEL " + model.getName() + " " + attribute_utils::parseAttributes(model, true) + "\n";
    }
    if (circuit.getSubcircuitStatus()) {
        result = ".SUBCKT " + circuit.getName() + " 0 "
                 + createSubcircuit(netOrderMap, netComponentsMap)
                 + "\n\n*circuit\n" + result + "\n.ENDS\n";
    }

    if (!circuit.getTran().getName().isEmpty()) {
        result += "\n.tran ";
        Component tran = circuit.getTran();\
            result += attribute_utils::parseAttributes(tran, false);
    }
    return result;
}
