#include "netlistproducer.h"
#include "src/utils/attributeutils.h"

#include <QMap>
#include <QSet>

NetlistProducer::NetlistProducer() {}

NetlistProducer::~NetlistProducer() {}

QString NetlistProducer::getValueOrDefault(QString string)
{
    return string.isEmpty() ? "_ " : string;
}

QString writeSignal(QString uuid, QMap<QString, int> netOrderMap)
{
    return uuid.isEmpty() ? "_ " : QString::number(netOrderMap[uuid]) + " ";
}

QString writeComponent(QString parentSignalUuid,
                           Component component,
                           QMap<QString, QList<Component>> netComponentsMap,
                           QMap<QString, int> netOrderMap,
                           QSet<QString> *usedComponents,
                           bool includeAttributeName)
{
    if (usedComponents->contains(component.getUuid()) || component.getValue() == "GND") {
        return "";
    }
    usedComponents->insert({component.getUuid()});
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
                                         usedComponents,
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

QString createSubcircuitLine(QMap<QString, int> netNumberMap,
                             QMap<QString, QList<Component>> netComponentsMap)
{
    QList<int> inOutList;
    for (auto const &key : netComponentsMap.keys()) {
        QList<Component> components = netComponentsMap[key];
        if (components.size() == 1) {
            inOutList.push_back(netNumberMap[key]);
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
    QMap<QString, int> netNumberMap;
    QMap<QString, QList<Component>> netComponentsMap = createNetComponentsMap(componentMap);
    QString firstComponentUuid;
    int lowestNumber = INT_MAX;
    for (const auto &net : netMap) {
        QString name = net.getName();
        if (name == "GND" || name == "") {
            netNumberMap.insert(net.getUuid(), 0);
        } else {
            int number = name.mid(1, name.size() - 1).toInt() * 10;
            netNumberMap[net.getUuid()] = number;
            if (number  < lowestNumber) {
                lowestNumber = number ;
                firstComponentUuid = net.getUuid();
            }
        }
    }
    Component component = findComponent(firstComponentUuid, componentMap);
    QSet<QString> usedComponents;
    QString netlist = writeComponent("", component, netComponentsMap, netNumberMap, &usedComponents, false);
    if (!circuit.getModelMap().empty()) {
        netlist += "\n";
    }
    for (const auto &model : circuit.getModelMap()) {
        netlist += ".MODEL " + model.getName() + " " + attribute_utils::parseAttributes(model, true) + "\n";
    }
    if (circuit.getSubcircuitStatus()) {
        netlist = ".SUBCKT " + circuit.getName() + " 0 "
                  + createSubcircuitLine(netNumberMap, netComponentsMap)
                 + "\n\n*circuit\n" + netlist + "\n.ENDS\n";
    }

    if (!circuit.getTran().getName().isEmpty()) {
        netlist += "\n.tran ";
        Component tran = circuit.getTran();\
            netlist += attribute_utils::parseAttributes(tran, false);
    }
    return netlist;
}
