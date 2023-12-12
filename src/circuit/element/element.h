#ifndef ELEMENT_H
#define ELEMENT_H

#include <QString>

class Element
{
private:
    QString uuid;
    QString name;

protected:
    QString elementType;
    virtual void setChildProperty(const QString &propertyName, const QString &property);

public:
    QString getUuid() const;
    QString getName() const;
    QString getElementType() const;
    void setProperty(const QString &propertyName, const QString &property);
    virtual void setProperty(const QString &propertyName, const Element *property);
};

#endif // ELEMENT_H
