#ifndef SPICEPRINTER_H
#define SPICEPRINTER_H

#include <QString>
#include <QMap>
#include <QSet>

#include <src/circuit/element/component.h>
#include <src/conversion/data/conversionparams.h>

class SpicePrinter
{
private:
    QMap<QString, QString> netLabelMap;
    QMap<QString, QSet<Component>> netComponentsMap;
    ConversionParams params;
    QString printOutput(Component component);

public:
    SpicePrinter();
    SpicePrinter(const QMap<QString, QString> &netLabelMap,
                     const QMap<QString, QSet<Component>> &netComponentsMap,
                     const ConversionParams &params);
    ~SpicePrinter();

    QString print(Component component, QString parentUUID = QString());
    QString printOutputs(QList<Component> components);
};

#endif // SPICEPRINTER_H
