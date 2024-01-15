#ifndef COMPONENTPRINTER_H
#define COMPONENTPRINTER_H

#include <QMap>
#include <QString>

#include <src/circuit/element/component.h>

class ComponentPrinter
{
private:
    QMap<QString, QString> netLabelMap;

public:
    ComponentPrinter(QMap<QString, QString> map);
    ComponentPrinter();
    ~ComponentPrinter();

    QString print(Component component, QString parentUUID = QString());
    QString printOutput(Component component);
};

#endif // COMPONENTPRINTER_H
