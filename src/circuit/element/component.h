#ifndef COMPONENT_H
#define COMPONENT_H

#include "attribute.h"
#include "device.h"
#include "signal.h"

#include <QList>
#include <QMap>

class Component : public Element
{
private:
    QString libComponent;
    QString libVariant;
    QString value;
    bool lockAssembly;
    QList<QString> list;
    QList<Attribute> attributeList;
    QList<Signal> signalList;
    const Device* device;
    void setChildProperty(const QString &propertyName, const QString &property);

public:
    Component();
    ~Component();

    QString getLibComponent() const;
    QString getLibVariant() const;
    QString getValue() const;
    bool getLockAssembly() const;
    QList<Attribute> getAttributeList() const;
    bool removeAttribute(Attribute attribute);
    QList<Signal> getSignalList() const;
    const Device getDevice() const;
    void setProperty(const QString &propertyName, const Element* property);
};

#endif // COMPONENT_H
