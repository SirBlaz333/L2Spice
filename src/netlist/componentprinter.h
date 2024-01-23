#ifndef COMPONENTPRINTER_H
#define COMPONENTPRINTER_H

#include <QString>
#include <QMap>
#include <QSet>

#include <src/circuit/element/component.h>

class ComponentPrinter
{
private:
    QMap<QString, QString> netLabelMap;
    QMap<QString, QSet<Component>> netComponentsMap;
    QString printOutput(Component component);

public:
    ComponentPrinter();
    ComponentPrinter(const QMap<QString, QString> &netLabelMap,
                     const QMap<QString, QSet<Component>> &netComponentsMap);
    ~ComponentPrinter();

    QString print(Component component, QString parentUUID = QString());
    QString printOutputs(QList<Component> components);
};

#endif // COMPONENTPRINTER_H
