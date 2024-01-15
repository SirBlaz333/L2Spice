#ifndef ATTRIBUTEUTILS_H
#define ATTRIBUTEUTILS_H

#include <QMap>
#include <QString>

#include <src/circuit/element/component.h>

typedef QMap<QString, QString> prefixesMap;

namespace attributeUtils {
Q_GLOBAL_STATIC(
    prefixesMap,
    prefixes,
    {{"pico", "p"}, {"nano", "n"}, {"micro", "u"}, {"milli", "m"}, {"kilo", "k"}, {"mega", "meg"}});

QString getUnitShortPrefix(QString unit);
QString getFullUnitPrefix(QString shortPrefix);
QString writeAttributes(Component component, bool includeName);
QString getUnitWithoutPrefix(QString unit);
QString getSourceType(QString value);
} // namespace attribute_utils

#endif // ATTRIBUTEUTILS_H
