#ifndef COMPONENT_H
#define COMPONENT_H

#include "attribute.h"
#include "device.h"
#include "signal.h"

#include <qhashfunctions.h>

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
    virtual ~Component();

    QString getLibComponent() const;
    QString getLibVariant() const;
    QString getValue() const;
    bool getLockAssembly() const;
    QList<Attribute> getAttributeList() const;
    bool removeAttribute(Attribute attribute);
    QList<Signal> getSignalList() const;
    const Device getDevice() const;
    void setProperty(const QString &propertyName, const QString &property);
    void setProperty(const QString &propertyName, const Element *property);
};


//for Qt 5
inline uint qHash(const Component &component, uint seed) noexcept
{
    QtPrivate::QHashCombine hash;
    seed = hash(seed, component.getName());
    seed = hash(seed, component.getUuid());
    return seed;
}

//for Qt 6
inline size_t qHash(const Component &component, size_t seed) noexcept
{
    QtPrivate::QHashCombine hash;
    seed = hash(seed, component.getName());
    seed = hash(seed, component.getUuid());
    return seed;
}

#endif // COMPONENT_H
