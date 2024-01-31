#ifndef SPICEPRINTER_H
#define SPICEPRINTER_H

#include <QMap>
#include <QSet>
#include <QString>

#include <src/circuit/element/component.h>
#include <src/conversion/data/conversionparams.h>

class SpicePrinter
{
private:
    QMap<QString, QString> netLabelMap;
    QMap<QString, QSet<Component>> netComponentsMap;
    ConversionParams params;
    QString printOutput(Component component);
    QString printMeter(Component component);
    QString printProbe(Component component);
    QString printModel(Component component);
    QString printComponent(Component component, QString parentUUID);

public:
    SpicePrinter(const QMap<QString, QString> &netLabelMap,
                 const QMap<QString, QSet<Component>> &netComponentsMap,
                 const ConversionParams &params);
    ~SpicePrinter();

    QString print(Component component, QString parentUUID = QString());
    QString printOutputs(QList<Component> components);
};

#endif // SPICEPRINTER_H
