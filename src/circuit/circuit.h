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
    const Variant* variant;
    const NetClass* netclass;
    const Component* tran = nullptr;
    QList<Net> nets;
    QList<Component> components;
    QList<Component> models;
    QList<Component> outputs;
    QList<Component> texts;

public:
    Circuit();
    ~Circuit();
    bool isEmpty() const;
    const Variant getVariant() const;
    const NetClass getNetclass() const;
    const Component getTran() const;
    QList<Net> getNets() const;
    QList<Component> getComponents() const;
    QList<Component> getModels() const;
    QList<Component> getOutputs() const;
    QList<Component> getTexts() const;
    void addElement(const Element *element);
};

#endif // CIRCUIT_H
