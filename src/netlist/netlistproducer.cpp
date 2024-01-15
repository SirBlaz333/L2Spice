#include "netlistproducer.h"

#include <QMap>
#include <QRegularExpression>
#include <QSet>

#include <src/file/filemanager.h>
#include <src/app/appsettings.h>
#include <src/utils/attributeutils.h>
#include <src/utils/regexutils.h>

NetlistProducer::NetlistProducer() {}

NetlistProducer::~NetlistProducer() {}

QString NetlistProducer::writeComponents(QString parentSignalUuid,
                           Component component,
                           QMap<QString, QList<Component>> netComponentsMap,
                           QMap<QString, QString> netLabelMap,
                           QSet<QString> *usedComponents)
{
    if (usedComponents->contains(component.getUuid()) || component.getValue() == "GND" || netComponentsMap.empty()) {
        return "";
    }
    usedComponents->insert({component.getUuid()});
    QString result = componentPrinter.print(component, parentSignalUuid).trimmed() + "\n";
    for (Signal signal : component.getSignalList()) {
        if (signal.getNet().getUuid() != parentSignalUuid) {
            QList<Component> componentList = netComponentsMap[signal.getNet().getUuid()];
            for (Component &component : componentList) {
                result += writeComponents(signal.getNet().getUuid(),
                                         component,
                                         netComponentsMap,
                                         netLabelMap,
                                         usedComponents);
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

QString createSubcircuitLine(QMap<QString, QString> netNumberMap,
                             QMap<QString, QList<Component>> netComponentsMap)
{
    QList<QString> inOutList;
    for (auto const &key : netComponentsMap.keys()) {
        QList<Component> components = netComponentsMap[key];
        if (components.size() == 1) {
            inOutList.push_back(netNumberMap[key]);
        }
    }
    std::sort(inOutList.begin(), inOutList.end());
    QString result;
    for (QString signalNumber : inOutList) {
        result += signalNumber + " ";
    }
    result.chop(1);
    return result;
}

void writeSubcircuit(QMap<QString, QString> *subcircuits, QString subcircuitName)
{
    if ((*subcircuits).contains(subcircuitName)) {
        return;
    }
    QString subcircuit = FileManager::loadFile(AppSettings::getSubcircuitDir() + subcircuitName + ".cir");
    (*subcircuits)[subcircuitName] = subcircuit;
    QRegularExpressionMatchIterator it = RegexUtils::subcircuitIdentifierRegex->globalMatch(subcircuit);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        writeSubcircuit(subcircuits, match.captured(1));
    }
}

void writeSubcircuit(QMap<QString, QString> *subcircuits, Component component)
{
    for (Attribute &attribute : component.getAttributeList()) {
        if (attribute.getName() == "SUBCIRCUIT_NAME") {
            writeSubcircuit(subcircuits, attribute.getValue());
            break;
        }
    }
}

QString getAllSubcircuits(QSet<QString> usedComponents, QMap<QString, Component> componentMap)
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
        if (!subcircuit.isEmpty()) {
            result += subcircuit + "\n";
        }
    }
    return result;
}

QMap<QString, QString> createNetLabelMap(QMap<QString, Net> netMap)
{
    QMap<QString, QString> netNumberMap;
    QSet<QString> usersNetLabels;
    for (const auto &net : netMap) {
        QString name = net.getName();
        if (name == "GND" || name == "") {
            netNumberMap.insert(net.getUuid(), "0");
        } else if (net.getAutoMode() == false) {
            netNumberMap[net.getUuid()] = net.getName();
            usersNetLabels.insert(net.getName());
        }
    }
    int counter = 1;
    for (const auto &net : netMap) {
        if (netNumberMap.contains(net.getUuid())) {
            continue;
        }
        QString number;
        do {
            number = QString::number(10 * counter++);
        } while (usersNetLabels.contains(number));
        netNumberMap[net.getUuid()] = number;
    }
    return netNumberMap;
}

QString getFirstComponentUuid(QMap<QString, QString> netNumberMap)
{
    for (const auto &key : netNumberMap.keys()) {
        if (netNumberMap[key] != "0") {
            return key;
        }
    }
    return "";
}

QString NetlistProducer::produceSpiceNotationNetlist(const Circuit &circuit)
{
    QMap<QString, Component> componentMap = circuit.getComponentMap();
    QMap<QString, QList<Component>> netComponentsMap = createNetComponentsMap(componentMap);
    QMap<QString, QString> netLabelMap = createNetLabelMap(circuit.getNetMap());
    Component component = findComponent(getFirstComponentUuid(netLabelMap), componentMap);
    QSet<QString> usedComponents;
    componentPrinter = ComponentPrinter(netLabelMap);
    QString netlist = writeComponents("", component, netComponentsMap, netLabelMap, &usedComponents);
    if (!circuit.getModelMap().empty()) {
        netlist += "\n";
        for (const auto &model : circuit.getModelMap()) {
            netlist += componentPrinter.print(model) + "\n";
        }
    }
    if (circuit.getSubcircuitStatus()) {
        netlist = ".SUBCKT " + circuit.getName() + " 0 "
                  + createSubcircuitLine(netLabelMap, netComponentsMap)
                 + "\n\n*circuit\n" + netlist + "\n.ENDS\n";
    } else {
        QString subcircuits = getAllSubcircuits(usedComponents, componentMap);
        netlist = subcircuits + netlist;

        if (!circuit.getTran().getName().isEmpty()) {
            netlist += componentPrinter.print(circuit.getTran());
        }
        if (!netlist.trimmed().isEmpty()) {
            netlist += "\n.end";
        }
    }
    return netlist.trimmed();
}
