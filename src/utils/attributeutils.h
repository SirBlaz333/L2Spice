#ifndef ATTRIBUTEUTILS_H
#define ATTRIBUTEUTILS_H

#include <QMap>
#include <QString>

#include <src/circuit/element/component.h>

namespace attribute_utils {
static QMap<QString, QString> prefixes = {{"pico", "p"},
                                                      {"nano", "n"},
                                                      {"micro", "u"},
                                                      {"milli", "m"},
                                                      {"kilo", "k"},
                                                      {"mega", "meg"}};

QString getUnitShortPrefix(QString unit);
QString getFullUnitPrefix(QString shortPrefix);
QString parseAttributes(Component component, bool includeName);
QString getUnitWithoutPrefix(QString unit);
}

#endif // ATTRIBUTEUTILS_H
