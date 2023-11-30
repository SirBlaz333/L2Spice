#include "netlistproducer.h"
#include "src/utils/attributeutils.h"

#include <QMap>
#include <QRegularExpression>
#include <QSet>

#include <src/file/filemanager.h>

const QRegularExpression NetlistProducer::subcircuitIdentifierRegex = QRegularExpression(R"(^X(\w+))", QRegularExpression::MultilineOption);

NetlistProducer::NetlistProducer() {}

NetlistProducer::~NetlistProducer() {}

QString writeSignal(QString uuid, QMap<QString, int> netOrderMap)
{
    return uuid.isEmpty() ? "_ " : QString::number(netOrderMap[uuid]) + " ";
}

QString writeComponent(Component component,
                       QString parentSignalUuid,
                       QMap<QString, int> netOrderMap,
                       bool includeAttributeName)
{
    QString result = component.getName() + " ";
    if (component.getValue() == "{{SUBCIRCUIT}}") {
        result = "X" + component.getAttributeList()[0].getValue() + " " + result;
    }
    if (!parentSignalUuid.isEmpty()) {
        result += writeSignal(parentSignalUuid, netOrderMap);
    }
    for (Signal signal : component.getSignalList()) {
        if (signal.getNet().getUuid() != parentSignalUuid) {
            result += writeSignal(signal.getNet().getUuid(), netOrderMap);
        }
    }
    result += attribute_utils::writeAttributes(component, includeAttributeName);
    result += "\n";
    return result;
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
    QString result = writeComponent(component, parentSignalUuid, netOrderMap, includeAttributeName);
    for (Signal signal : component.getSignalList()) {
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

void NetlistProducer::writeSubcircuit(QMap<QString, QString> *subcircuits, QString subcircuitName)
{
    if ((*subcircuits).contains(subcircuitName)) {
        return;
    }
    QString subcircuit = FileManager::loadSubcircuit(subcircuitName);
    (*subcircuits)[subcircuitName] = subcircuit;
    QRegularExpressionMatchIterator it = subcircuitIdentifierRegex.globalMatch(subcircuit);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        writeSubcircuit(subcircuits, match.captured(1));
    }
}

void NetlistProducer::writeSubcircuit(QMap<QString, QString> *subcircuits, Component component)
{
    for (Attribute &attribute : component.getAttributeList()) {
        if (attribute.getName() == "SUBCIRCUIT_NAME") {
            writeSubcircuit(subcircuits, attribute.getValue());
            break;
        }
    }
}

QString NetlistProducer::getAllSubcircuits(QSet<QString> usedComponents, QMap<QString, Component> componentMap)
{
    QMap<QString, QString> subcircuits;
    for (const auto &uuid : usedComponents) {
        Component component = componentMap[uuid];
        if (component.getValue() == "{{SUBCIRCUIT}}") {
            writeSubcircuit(&subcircuits, component);
        }
    }
    QString result;
    for (const auto &subcircuit : subcircuits) {
        result += subcircuit + "\n";
    }
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
        netlist += ".MODEL " + model.getName() + " " + attribute_utils::writeAttributes(model, true) + "\n";
    }
    if (circuit.getSubcircuitStatus()) {
        netlist = ".SUBCKT " + circuit.getName() + " 0 "
                  + createSubcircuitLine(netNumberMap, netComponentsMap)
                 + "\n\n*circuit\n" + netlist + "\n.ENDS\n";
    } else {
        QString subcircuits = getAllSubcircuits(usedComponents, componentMap);
        netlist = subcircuits + netlist;
    }

    if (!circuit.getTran().getName().isEmpty()) {
        netlist += "\n.tran ";
        Component tran = circuit.getTran();\
            netlist += attribute_utils::writeAttributes(tran, false);
    }
    return netlist;
}
