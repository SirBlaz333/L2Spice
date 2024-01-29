#include "spiceprinter.h"
#include "src/utils/attributeutils.h"

Q_GLOBAL_STATIC(QString, EMPTY_STRING, QString());
Q_GLOBAL_STATIC(QString, MODEL, QString(".MODEL %1 %2"));
Q_GLOBAL_STATIC(QString, TRAN, QString("\n.tran %1"));
Q_GLOBAL_STATIC(QString, PROBE, QString(".PRINT %1 %2 0\n"));
Q_GLOBAL_STATIC(QString, METER, QString(".PRINT %1 %2\n"));
Q_GLOBAL_STATIC(QString, NODEV, QString(".PRINT NODEV %1 %2\n"));
Q_GLOBAL_STATIC(QString, NODEP, QString(".PRINT NODEP %1 %2\n"));
Q_GLOBAL_STATIC(QString, SUBCIRCUIT, QString("X%1 %2"));
Q_GLOBAL_STATIC(QString, FILE_OUTPUT, QString(".FILE %1\n"));
Q_GLOBAL_STATIC(QString, WORD_SEPARATOR, QString(" "));
Q_GLOBAL_STATIC(int, JSIM, 0);
Q_GLOBAL_STATIC(QSet<QString>, JSIM_MODEL_ATTRIBUTES,
                {"RTYPE", "CCT", "VG", "DELV", "ICON", "R0", "RN", "CAP", "ICRIT"});

SpicePrinter::SpicePrinter(const QMap<QString, QString> &netLabelMap,
                                   const QMap<QString, QSet<Component> > &netComponentsMap,
                                   const ConversionParams &params)
    : netLabelMap(netLabelMap)
    , netComponentsMap(netComponentsMap)
    , params(params)
{}

SpicePrinter::SpicePrinter() {}

SpicePrinter::~SpicePrinter() {}

QString writeSignal(QString uuid, QMap<QString, QString> netLabelMap)
{
    return uuid.isEmpty() || netLabelMap.isEmpty() ? "_ " : netLabelMap[uuid];
}

QString printComponent(Component component, QString parentUUID, QMap<QString, QString> netLabelMap)
{
    QString result = component.getName() + *WORD_SEPARATOR;
    QList<Attribute> list = component.getAttributeList();
    if (component.getValue() == "{{SUBCIRCUIT}}") {
        result = SUBCIRCUIT->arg(list.first().getValue().toUpper(), result);
        component.removeAttribute(list.first());
    }
    if (!parentUUID.isEmpty()) {
        result += writeSignal(parentUUID, netLabelMap) + *WORD_SEPARATOR;
    }
    for (Signal &signal : component.getSignalList()) {
        if (signal.getNet().getUuid() != parentUUID) {
            result += writeSignal(signal.getNet().getUuid(), netLabelMap) + *WORD_SEPARATOR;
        }
    }
    if (component.getValue() == "VCC") {
        result += "0 ";
    }
    result += attributeUtils::writeAttributes(component, false);
    return result;
}

QString printModel(Component model, bool isJSIM)
{
    QList<Attribute> attributes = model.getAttributeList();
    if(isJSIM) {
        auto condition = [](Attribute attribute) { return !JSIM_MODEL_ATTRIBUTES->contains(attribute.getName()); };
        attributes.erase(std::remove_if(attributes.begin(), attributes.end(), condition));
    }
    return MODEL->arg(model.getName(), attributeUtils::writeAttributes(attributes, model.getValue(), true));
}

QString printTran(Component tran)
{
    for (Attribute &attribute : tran.getAttributeList()) {
        if (attribute.getName() == "ANALYSIS") {
            tran.removeAttribute(attribute);
            break;
        }
    }
    return TRAN->arg(attributeUtils::writeAttributes(tran, false));
}

QString SpicePrinter::print(Component component, QString parentUUID)
{
    QString elementType = component.getElementType();
    if (elementType == "component") {
        return printComponent(component, parentUUID, netLabelMap);
    }
    if (elementType == "model") {
        return printModel(component, params.getConvertorVersion() == *JSIM);
    }
    if (elementType == "tran") {
        return printTran(component);
    }
    return *EMPTY_STRING;
}

QString printProbe(Component component, QMap<QString, QString> netLabelMap) {
    Attribute printType;
    for (Attribute &attribute : component.getAttributeList()) {
        if (attribute.getName() == "PRINT_TYPE") {
            printType = attribute;
        }
    }
    QString signal = writeSignal(component.getSignalList().constFirst().getNet().getUuid(), netLabelMap);
    return PROBE->arg(printType.getValue(), signal);
}


QString* getNodevMode(Attribute printType)
{
    if (printType.getValue() == "PHASE") {
        return NODEP;
    }
    return NODEV;
}

QString printNodev(Attribute printType, QMap<QString, QString> netLabelMap, QString firstUuid, QString secondUuid) {
    return getNodevMode(printType)->arg(netLabelMap.value(firstUuid), netLabelMap.value(secondUuid));
}

QString printMeter(Component component,
                   QMap<QString, QString> netLabelMap,
                   QMap<QString, QSet<Component>> netComponentsMap)
{
    QString firstUuid = component.getSignalList().constFirst().getNet().getUuid();
    QString secondUuid = component.getSignalList().constLast().getNet().getUuid();
    QSet<Component> first = netComponentsMap.value(firstUuid);
    QSet<Component> second = netComponentsMap.value(secondUuid);
    Attribute device, printType;
    for (Attribute &attribute : component.getAttributeList()) {
        if (attribute.getName() == "DEVICE_NAME") {
            device = attribute;
        }
        if (attribute.getName() == "PRINT_TYPE") {
            printType = attribute;
        }
    }
    if (first.isEmpty() || second.isEmpty()) {
        return printNodev(printType, netLabelMap, firstUuid, secondUuid);
    }
    QList<Component> intersection;
    for (const Component &component : first) {
        if (second.contains(component)) {
            intersection.append(component);
        }
    }
    if (intersection.size() != 1
        || (!device.getValue().isEmpty() && device.getValue() != intersection.first().getName())) {
        return printNodev(printType, netLabelMap, firstUuid, secondUuid);
    }
    return METER->arg(printType.getValue(), intersection.first().getName());
}

QString SpicePrinter::printOutput(Component component) {
    if (component.getElementType() == "probe") {
        return printProbe(component, netLabelMap);
    }
    if (component.getElementType() == "meter") {
        return printMeter(component, netLabelMap, netComponentsMap);
    }
    return *EMPTY_STRING;
}

QString SpicePrinter::printOutputs(QList<Component> components)
{
    if (!params.getConsoleOutput() && !params.getFileOutput()) {
        return *EMPTY_STRING;
    }
    QMap<QString, QList<Component>> outputsMap;
    for (Component &component : components) {
        QString fileName = *EMPTY_STRING;
        for (Attribute &attribute : component.getAttributeList()) {
            if (attribute.getName() == "FILENAME") {
                fileName = attribute.getValue();
            }
        }
        QList<Component> assignedComponents = outputsMap.value(fileName);
        assignedComponents.append(component);
        outputsMap.insert(fileName, assignedComponents);
    }
    if (!params.getConsoleOutput()) {
        outputsMap.remove(*EMPTY_STRING);
    }
    QString result;
    QList<QString> fileNames = outputsMap.keys();
    fileNames.sort();
    for (QString &fileName : fileNames) {
        if (!fileName.isEmpty() && params.getFileOutput()) {
            result += FILE_OUTPUT->arg(fileName);
        }
        for (Component &component : outputsMap.value(fileName)) {
            result += printOutput(component);
        }
    }
    return result;
}
