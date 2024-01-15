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
    QList<Net> nets;
    QList<Component> components;
    QList<Component> models;
    QList<Component> outputs;

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
    void addElement(const Element *element);
    void setSubcircuitStatus(bool isSubcircuit, QString name);
    bool getSubcircuitStatus() const;
    QString getName() const;
};

#endif // CIRCUIT_H
