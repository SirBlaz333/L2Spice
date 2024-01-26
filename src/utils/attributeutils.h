#ifndef ATTRIBUTEUTILS_H
#define ATTRIBUTEUTILS_H

#include <QMap>
#include <QString>

#include <src/circuit/element/component.h>

namespace attributeUtils {
QString getUnitShortPrefix(QString unit);
QString getFullUnitPrefix(QString shortPrefix);
QString writeAttributes(Component component, bool includeName);
QString getUnitWithoutPrefix(QString unit);
QString getSourceType(QString value);
} // namespace attribute_utils

#endif // ATTRIBUTEUTILS_H
