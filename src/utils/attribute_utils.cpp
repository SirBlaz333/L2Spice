#include "attribute_utils.h"
#include "src/utils/regex_utils.h"

#include <QRegularExpression>

const QMap<QString, QString> prefixes =
 {{"pico", "p"}, {"nano", "n"}, {"micro", "u"}, {"milli", "m"}, {"kilo", "k"}, {"mega", "meg"}};
const QString EMPTY_STRING = QString();
const int SOURCE_GROUP = 1;

QString attributeUtils::getUnitShortPrefix(QString unit)
{
    for (const auto &key : prefixes.keys()) {
        if (unit.contains(key)) {
            return prefixes.value(key);
        }
    }
    return EMPTY_STRING;
}

QString attributeUtils::getFullUnitPrefix(QString shortPrefix)
{
    for (const auto &key : prefixes.keys()) {
        if (shortPrefix == prefixes.value(key)) {
            return key;
        }
    }
    return EMPTY_STRING;
}

QString writeAttribute(Attribute attribute, bool includeName)
{
    QString result = includeName ? attribute.getName() + "=" : EMPTY_STRING;
    return result + attribute.getValue() + attributeUtils::getUnitShortPrefix(attribute.getUnit()) + " ";
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

QString attributeUtils::writeAttributes(QList<Attribute> attributes, QString value, bool includeName)
{
    QList<Attribute>::iterator begin = attributes.begin();
    QList<Attribute>::iterator end = attributes.end();
    QString sourceType = getSourceType(value);
    QString attributesLine = writeAttributes(begin, end, includeName);
    return sourceType == EMPTY_STRING ? attributesLine : sourceType.toLower() + "(" + attributesLine + ")";
}

QString attributeUtils::getUnitWithoutPrefix(QString unit)
{
    for (const auto &key : prefixes.keys()) {
        if (unit.contains(key)) {
            return unit.mid(key.length(), unit.length());
        }
    }
    return unit;
}

QString attributeUtils::getSourceType(QString value)
{
    QRegularExpressionMatch match = RegexUtils::sourceTypeRegex.match(value);
    if (match.hasMatch()) {
        return match.captured(SOURCE_GROUP);
    }
    return match.hasMatch() ? match.captured(SOURCE_GROUP) : EMPTY_STRING;
}
