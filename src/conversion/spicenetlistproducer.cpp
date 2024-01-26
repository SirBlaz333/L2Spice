#include "spicenetlistproducer.h"

#include <QMap>
#include <QRegularExpression>
#include <QSet>

#include <src/file/filemanager.h>
#include <src/app/appsettings.h>
#include <src/utils/attributeutils.h>
#include <src/utils/regexutils.h>

SpiceNetlistProducer::SpiceNetlistProducer() {}

SpiceNetlistProducer::~SpiceNetlistProducer() {}

QString SpiceNetlistProducer::writeComponents(QString parentSignalUuid,
                           Component component,
                           ComponentPrinter printer,
                           QMap<QString, QSet<Component>> netComponentsMap,
                           QSet<QString> *usedComponents)
{
    if (usedComponents->contains(component.getUuid()) || component.getValue() == "GND" || netComponentsMap.empty()) {
        return "";
    }
    usedComponents->insert(component.getUuid());
    QString result = printer.print(component, parentSignalUuid).trimmed() + "\n";
    for (Signal &signal : component.getSignalList()) {
        if (signal.getNet().getUuid() != parentSignalUuid) {
            QSet<Component> componentList = netComponentsMap[signal.getNet().getUuid()];
            for (const Component &component : componentList) {
                result += writeComponents(signal.getNet().getUuid(), component, printer, netComponentsMap, usedComponents);
            }
        }
    }
    return result;
}

QMap<QString, QSet<Component>> createNetComponentsMap(QList<Component> components)
{
    QMap<QString, QSet<Component>> map;
    for (Component &component : components) {
        QList<Signal> signalList = component.getSignalList();
        for (Signal &signal : signalList) {
            QSet<Component> components = map[signal.getNet().getUuid()];
            components.insert(component);
            map[signal.getNet().getUuid()] = components;
        }
    }
    return map;
}

Component findComponent(QString uuid, QList<Component> componentMap)
{
    for (Component &component: componentMap) {
        for (Signal &signal : component.getSignalList()) {
            if (signal.getNet().getUuid() == uuid) {
                return component;
            }
        }
    }
    return Component();
}

QString createSubcircuitLine(QMap<QString, QString> netNumberMap,
                             QMap<QString, QSet<Component>> netComponentsMap)
{
    QList<QString> inOutList;
    for (auto const &key : netComponentsMap.keys()) {
        QSet<Component> components = netComponentsMap[key];
        if (components.size() == 1) {
            inOutList.push_back(netNumberMap[key]);
        }
    }
    std::sort(inOutList.begin(), inOutList.end());
    QString result;
    for (QString &signalNumber : inOutList) {
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

QString getAllSubcircuits(QSet<QString> usedComponents, QList<Component> components)
{
    QMap<QString, QString> subcircuits;
    for (Component &component : components) {
        if (usedComponents.contains(component.getUuid()) && component.getValue() == "{{SUBCIRCUIT}}") {
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

QMap<QString, QString> createNetLabelMap(QList<Net> netMap)
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

QString SpiceNetlistProducer::produceSpiceNotationNetlist(const Circuit &circuit, const ConversionParams &params)
{
    QList<Component> components = circuit.getComponents();
    QMap<QString, QSet<Component>> netComponentsMap = createNetComponentsMap(components);
    QMap<QString, QString> netLabelMap = createNetLabelMap(circuit.getNets());
    Component component = findComponent(getFirstComponentUuid(netLabelMap), components);
    QSet<QString> usedComponents;
    ComponentPrinter printer(netLabelMap, netComponentsMap, params);
    QString netlist = writeComponents("", component, printer, netComponentsMap, &usedComponents);
    if (!circuit.getModels().empty()) {
        netlist += "\n";
        for (Component &model : circuit.getModels()) {
            netlist += printer.print(model) + "\n";
        }
    }
    if (params.getSubcircuitStatus()) {
        netlist = ".SUBCKT " + params.getSubcircuitName() + " 0 "
                  + createSubcircuitLine(netLabelMap, netComponentsMap)
                 + "\n\n*circuit\n" + netlist + "\n.ENDS\n";
    } else {
        QString subcircuits = getAllSubcircuits(usedComponents, components);
        netlist = subcircuits + netlist;

        if (!circuit.getOutputs().empty() && (params.getConsoleOutput() || params.getFileOutput())) {
            netlist += "\n" + printer.printOutputs(circuit.getOutputs());
        }
        if (!circuit.getTran().getName().isEmpty()) {
            netlist += printer.print(circuit.getTran());
        }
        if (!netlist.trimmed().isEmpty()) {
            netlist += "\n.end";
        }
    }
    return netlist.trimmed();
}
