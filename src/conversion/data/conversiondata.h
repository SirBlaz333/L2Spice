#ifndef CONVERSIONDATA_H
#define CONVERSIONDATA_H

#include <QString>

class ConversionData
{
    bool empty;
    QString name;
    QString libreNetlist;
    QString spiceNetlist;
public:
    ~ConversionData();
    ConversionData();
    ConversionData(const QString &name, const QString &libreNetlist, const QString &spiceNetlist);
    bool isEmpty();
    QString getName() const;
    QString getLibreNetlist() const;
    QString getSpiceNetlist() const;
};

#endif // CONVERSIONDATA_H
