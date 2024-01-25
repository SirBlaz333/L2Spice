#include "conversiondata.h"

QString ConversionData::getName() const
{
    return name;
}

QString ConversionData::getLibreNetlist() const
{
    return libreNetlist;
}

QString ConversionData::getSpiceNetlist() const
{
    return spiceNetlist;
}

ConversionData::~ConversionData() {}

ConversionData::ConversionData()
{
    name = "none";
    empty = true;
}

ConversionData::ConversionData(const QString &name, const QString &libreNetlist, const QString &spiceNetlist)
    : name(name)
    , libreNetlist(libreNetlist)
    , spiceNetlist(spiceNetlist)
{
    empty = false;
}

bool ConversionData::isEmpty()
{
    return empty;
}
