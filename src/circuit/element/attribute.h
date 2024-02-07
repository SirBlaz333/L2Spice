#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include "element.h"

class Attribute : public Element
{
private:
    QString type;
    QString unit;
    QString value;

    void setChildProperty(const QString &propertyName, const QString &property);

public:
    Attribute();
    virtual ~Attribute();

    QString getType() const;
    QString getUnit() const;
    QString getValue() const;
};

#endif // ATTRIBUTE_H
