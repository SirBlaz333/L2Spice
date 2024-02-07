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

inline size_t qHash(const Element &elements, size_t seed) noexcept
{
    QtPrivate::QHashCombine hash;
    seed = hash(seed, elements.getName());
    seed = hash(seed, elements.getUuid());
    return seed;
}

#endif // ELEMENT_H
