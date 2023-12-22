#ifndef REGEXUTILS_H
#define REGEXUTILS_H

#include <QRegularExpression>

namespace RegexUtils {
    Q_GLOBAL_STATIC(QRegularExpression, componentRegex,
                    QRegularExpression(R"(\(component.+?\n\s\))", QRegularExpression::DotMatchesEverythingOption));
    Q_GLOBAL_STATIC(QRegularExpression, nameRegex,
                    QRegularExpression(R"(\(name \"(.+?)\"\))"));
    Q_GLOBAL_STATIC(QRegularExpression, paramRegex,
                    QRegularExpression(R"((\d*)(\w*))"));
    Q_GLOBAL_STATIC(QRegularExpression, attributeRegex,
                    QRegularExpression(R"(\(attribute \"\w+\" \(type \w+\) (\(unit (\w+)\)) (\(value \"([\d\w]*)\"\))\))"));
    Q_GLOBAL_STATIC(QRegularExpression, signalRegex,
                    QRegularExpression(R"(\(signal .+? \(net .+?\)\))"));
    Q_GLOBAL_STATIC(QRegularExpression, sourceTypesRegex,
                    QRegularExpression(R"(DC|PWL|PULSE|SIN|CUS|NOISE|EXP)", QRegularExpression::CaseInsensitiveOption));
    Q_GLOBAL_STATIC(QRegularExpression, subcircuitRegex,
                    QRegularExpression(R"(\.SUBCKT (\w+) .+?\.ENDS\n)", QRegularExpression::DotMatchesEverythingOption));
    Q_GLOBAL_STATIC(QRegularExpression, subcircuitIdentifierRegex,
                    QRegularExpression(R"(^X(\w+))", QRegularExpression::MultilineOption));
    Q_GLOBAL_STATIC(QRegularExpression, sourceTypeRegex,
                    QRegularExpression(R"({{\w+/(\w+)}})"));
};

#endif // REGEXUTILS_H
