#ifndef ELEMENT_H
#define ELEMENT_H

#include <QString>
#include <qhashfunctions.h>

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
    bool operator==(const Element &other) const
    {
        return this->uuid == other.uuid && this->name == other.name;
    }
};

inline size_t qHash(const Element &element, size_t seed) noexcept
{
    QtPrivate::QHashCombine hash;
    seed = hash(seed, element.getName());
    seed = hash(seed, element.getUuid());
    return seed;
}

#endif // ELEMENT_H
