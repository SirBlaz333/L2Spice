#ifndef ATTRIBUTE_UTILS_H
#define ATTRIBUTE_UTILS_H

#include <QMap>
#include <QString>

#include <src/circuit/element/component.h>

namespace AttributeUtils {
/**
 * @param unit - physical unit with prefix.
 * @return short version of prefix.
 */
QString getUnitShortPrefix(QString unit);

/**
 * @param shortPrefix - short prefix.
 * @return full prefix.
 */
QString getFullUnitPrefix(QString shortPrefix);

/**
 * Creates a string representation of the attributes.
 *
 * @param attributes - list of the attributes to write.
 * @param value - value of the parent component from LibrePCB circuit.
 * @param includeName - whether the name of the attribute should be included or not.
 * @return a string representation of the attributes.
 */
QString writeAttributes(QList<Attribute> attibutes, QString value = QString(), bool includeName = false);

/**
 * Remove the prefix from the unit.
 *
 * @param unit - a unit with a prefix or not.
 * @return the unit without a prefix.
 */
QString getUnitWithoutPrefix(QString unit);

/**
 * Extracts the source type from the value of the LibrePCB component.
 *
 * @param value - the value of the LibrePCB component.
 * @return the source type.
 */
QString getSourceType(QString value);
} // namespace attribute_utils

#endif // ATTRIBUTE_UTILS_H
