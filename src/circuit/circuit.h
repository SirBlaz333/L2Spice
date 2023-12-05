#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <QMap>
#include <QString>
#include <src/circuit/element/component.h>
#include <src/circuit/element/net.h>
#include <src/circuit/element/netclass.h>

class Circuit
{
private:
    bool empty = true;
    bool isSubcircuit;
    QString name;
    const Variant* variant;
    const NetClass* netclass;
    const Component* tran = nullptr;
    QMap<QString, Net> netMap;
    QMap<QString, Component> componentMap;
    QMap<QString, Component> modelMap;

public:
    Circuit();
    ~Circuit();
    bool isEmpty() const;
    const Variant getVariant() const;
    const NetClass getNetclass() const;
    const Component getTran() const;
    QMap<QString, Net> getNetMap() const;
    QMap<QString, Component> getComponentMap() const;
    QMap<QString, Component> getModelMap() const;
    void addElement(const Element *element);
    void setSubcircuitStatus(bool isSubcircuit, QString name);
    bool getSubcircuitStatus() const;
    QString getName() const;
};

#endif // CIRCUIT_H
