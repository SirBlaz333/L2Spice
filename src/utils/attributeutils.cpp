#include "attributeutils.h"

#include <QRegularExpression>

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

QString writeAttributes(QList<Attribute>::iterator begin, QList<Attribute>::iterator end, bool includeName)
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

QString attribute_utils::writeAttributes(Component component, bool includeName)
{
    QList<Attribute> attributes = component.getAttributeList();
    QList<Attribute>::iterator begin = attributes.begin();
    QList<Attribute>::iterator end = attributes.end();
    QString sourceType = getSourceType(component.getValue());
    QString attributesLine = writeAttributes(begin, end, includeName);
    return sourceType == "" ? attributesLine : sourceType.toLower() + "(" + attributesLine + ")";
}

QString attribute_utils::getUnitWithoutPrefix(QString unit)
{
    for (const auto &key : prefixes.keys()) {
        if (unit.contains(key)) {
            return unit.mid(key.length(), unit.length());
        }
    }
    return unit;
}

QString attribute_utils::getSourceType(QString value)
{
    QRegularExpression sourceTypeRegex(R"({{\w+/(\w+)}})");
    QRegularExpressionMatch match = sourceTypeRegex.match(value);
    QList<QString> list = match.capturedTexts();
    if (match.hasMatch()) {
        return match.captured(1);
    }
    return match.hasMatch() ? match.captured(1) : "";
}
