#include "spice_netlist_producer.h"

#include <QMap>
#include <QRegularExpression>
#include <QSet>

#include <src/app/app_settings.h>
#include <src/file/file_manager.h>
#include <src/utils/attribute_utils.h>
#include <src/utils/regex_utils.h>

const QString EMPTY_STRING = QString();
const QString LINE_SEPARATOR = QString("<br>");
const QString SUBCIRCUIT = QString(".SUBCKT %1 0 %2<br><br>*circuit<br>%3<br>.ENDS<br>");
const int ONE_CONNECTION = 1;
const int CONNECTION_ID_MULTIPLIER = 10;
const QString SUBCIRCUIT_VALUE = "{{SUBCIRCUIT}}";
const QString SUBCIRCUIT_NAME = "SUBCIRCUIT_NAME";
const QString GROUND = QString("GND");
const QString GROUND_ID = QString("0");
const QString END = QString(".end");
const QString DEFAULT_MODEL = QString(".MODEL %1 jj(%2)");
const QString MODEL_NAME = QString("name");

QString SpiceNetlistProducer::writeComponents(QString parentSignalUuid,
                                              Component component,
                                              SpicePrinter printer,
                                              QMap<QString, QSet<Component>> netComponentsMap,
                                              QSet<QString> *usedComponents)
{
    if (usedComponents->contains(component.getUuid())
        || component.getValue() == GROUND
        || netComponentsMap.empty()) {
        return EMPTY_STRING;
    }
    usedComponents->insert(component.getUuid());
    QString result = printer.print(component, parentSignalUuid).trimmed() + LINE_SEPARATOR;
    for (Signal &signal : component.getSignalList()) {
        if (signal.getNet().getUuid() != parentSignalUuid) {
            QSet<Component> componentList = netComponentsMap[signal.getNet().getUuid()];
            for (const Component &component : componentList) {
                result += writeComponents(signal.getNet().getUuid(),
                                          component,
                                          printer,
                                          netComponentsMap,
                                          usedComponents);
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
    for (Component &component : componentMap) {
        for (Signal &signal : component.getSignalList()) {
            if (signal.getNet().getUuid() == uuid) {
                return component;
            }
        }
    }
    return Component();
}

QString getSubcircuitIO(QMap<QString, QString> netNumberMap,
                        QMap<QString, QSet<Component>> netComponentsMap)
{
    QList<QString> inOutList;
    for (auto const &key : netComponentsMap.keys()) {
        QSet<Component> components = netComponentsMap[key];
        if (components.size() == ONE_CONNECTION) {
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
    QString subcircuitFile = AppSettings::getSubcircuitDir() + "/" + subcircuitName + ".cir";
    QString subcircuit = FileManager::loadFile(subcircuitFile);
    subcircuit.replace("\n", LINE_SEPARATOR);
    (*subcircuits)[subcircuitName] = subcircuit;
    QRegularExpressionMatchIterator it = RegexUtils::subcircuitIdentifierRegex.globalMatch(subcircuit);
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        writeSubcircuit(subcircuits, match.captured(1));
    }
}

void writeSubcircuit(QMap<QString, QString> *subcircuits, Component component)
{
    for (Attribute &attribute : component.getAttributeList()) {
        if (attribute.getName() == SUBCIRCUIT_NAME) {
            writeSubcircuit(subcircuits, attribute.getValue());
            break;
        }
    }
}

QString getAllSubcircuits(QSet<QString> usedComponents, QList<Component> components)
{
    QMap<QString, QString> subcircuits;
    for (Component &component : components) {
        if (usedComponents.contains(component.getUuid())
            && component.getValue() == SUBCIRCUIT_VALUE) {
            writeSubcircuit(&subcircuits, component);
        }
    }
    QString result;
    for (const auto &subcircuit : subcircuits) {
        if (!subcircuit.isEmpty()) {
            result += subcircuit + LINE_SEPARATOR + LINE_SEPARATOR;
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
        if (name == GROUND || name.isEmpty()) {
            netNumberMap.insert(net.getUuid(), GROUND_ID);
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
            number = QString::number(CONNECTION_ID_MULTIPLIER * counter++);
        } while (usersNetLabels.contains(number));
        netNumberMap[net.getUuid()] = number;
    }
    return netNumberMap;
}

QString getFirstComponentUuid(QMap<QString, QString> netNumberMap)
{
    for (const auto &key : netNumberMap.keys()) {
        if (netNumberMap[key] != GROUND_ID) {
            return key;
        }
    }
    return EMPTY_STRING;
}

QSet<QString> findAllUsedModel(QString netlist)
{
    QSet<QString> usedModels;
    QRegularExpressionMatchIterator it = RegexUtils::jjSpiceRow.globalMatch(netlist);
    while (it.hasNext()) {
        usedModels.insert(it.next().captured(1));
    }
    return usedModels;
}

Component createFakeModel()
{
    Component modelComponent;
    modelComponent.setProperty("value", "{{MODEL/JJ}}");
    QList<QPair<QString, QString>> model = AppSettings::getDefaultModel();
    for (QPair<QString, QString> &pair : model) {
        QSharedPointer<Element> attribute = QSharedPointer<Attribute>::create();
        attribute->setProperty("name", pair.first);
        attribute->setProperty("value", pair.second);
        modelComponent.setProperty("attribute", attribute.get());
    }
    return modelComponent;
}

QString SpiceNetlistProducer::produceSpiceNetlist(const Circuit &circuit,
                                                          const ConversionParams &params)
{
    QList<Component> components = circuit.getComponents();
    QMap<QString, QSet<Component>> netComponentsMap = createNetComponentsMap(components);
    QMap<QString, QString> netLabelMap = createNetLabelMap(circuit.getNets());
    Component component = findComponent(getFirstComponentUuid(netLabelMap), components);
    QSet<QString> usedComponents;
    SpicePrinter printer(netLabelMap, netComponentsMap, params);
    QString netlist = writeComponents(EMPTY_STRING,
                                      component,
                                      printer,
                                      netComponentsMap,
                                      &usedComponents);
    if (!circuit.getTexts().empty()) {
        netlist = printer.printTexts(circuit.getTexts()) + netlist;
    }

    QSet<QString> usedModels = findAllUsedModel(netlist);
    if (!usedModels.empty()) {
        netlist += LINE_SEPARATOR;
        for (Component &model : circuit.getModels()) {
            netlist += printer.print(model) + LINE_SEPARATOR;
            usedModels.remove(model.getName());
        }
        Component fakeModel = createFakeModel();
        for (const QString &modelName : usedModels) {
            fakeModel.setProperty(MODEL_NAME, modelName);
            netlist += printer.print(fakeModel) + LINE_SEPARATOR;
        }
    }
    if (params.getSubcircuitStatus()) {
        QString io = getSubcircuitIO(netLabelMap, netComponentsMap);
        netlist = SUBCIRCUIT.arg(params.getSubcircuitName(), io, netlist);
    } else {
        QString subcircuits = getAllSubcircuits(usedComponents, components);
        netlist = subcircuits + netlist;

        if (!circuit.getOutputs().empty() && (params.getConsoleOutput() || params.getFileOutput())) {
            netlist += LINE_SEPARATOR + printer.printOutputs(circuit.getOutputs());
        }
        if (!circuit.getTran().getName().isEmpty()) {
            netlist += LINE_SEPARATOR + printer.print(circuit.getTran());
        }
        if (!netlist.trimmed().isEmpty()) {
            netlist += LINE_SEPARATOR + END;
        }
    }
    return netlist.trimmed();
}
