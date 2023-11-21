#include "../headers/attributeutils.h"

QString attribute_utils::getUnitShortPrefix(QString unit)
{
    for (const auto &key : prefixes.keys()) {
        if (unit.contains(key)) {
            return prefixes[key];
        }
    }
    return "";
}

QString attribute_utils::getFullUnitPrefix(QString shortPrefix)
{
    for (const auto &key : prefixes.keys()) {
        if (shortPrefix == prefixes[key]) {
            return key;
        }
    }
    return "";
}

QString writeAttribute(Attribute attribute, bool includeName)
{
    QString result = includeName ? attribute.getName() + "=" : "";
    return result + attribute.getValue() + attribute_utils::getUnitShortPrefix(attribute.getUnit()) + " ";
}

QString parseAttributes(QList<Attribute>::iterator begin, QList<Attribute>::iterator end, bool includeName)
{
    QString result;
    while (begin != end) {
        if (!begin->getValue().isEmpty()) {
            result += writeAttribute(*begin, includeName);
        }
        begin++;
    }
    if (!result.isEmpty()) {
        result.chop(1);
    }
    return result;
}

QString attribute_utils::parseAttributes(Component component, bool includeName)
{
    QList<Attribute> attributes = component.getAttributeList();
    QList<Attribute>::iterator begin = attributes.begin();
    QList<Attribute>::iterator end = attributes.end();
    if (begin->getName() == "ANALYSIS") {
        begin++;
    }
    if (begin->getName() == "SOURCETYPE") {
        QString result = begin->getValue() + "(";
        return result + parseAttributes(++begin, end, includeName) + ")";
    }
    return parseAttributes(begin, end, includeName);
}

QString attribute_utils::getUnitWithoutPrefix(QString unit)
{
    for (const auto &key : prefixes.keys()) {
        if (unit.contains(key)) {
            return unit.mid(0, key.length());
        }
    }
    return unit;
}
