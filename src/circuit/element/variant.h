#ifndef VARIANT_H
#define VARIANT_H

#include "element.h"

class Variant : public Element
{
private:
    QString description;
    void setChildProperty(const QString &propertyName, const QString &property);

public:
    Variant();
    ~Variant();
    QString getDescription() const;

};

#endif // VARIANT_H
