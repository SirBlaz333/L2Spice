#ifndef APP_HEADER_H
#define APP_HEADER_H

#include <QString>

#include <src/conversion/data/conversion_params.h>

class AppHeader
{
public:
    AppHeader();
    QString getHeader(ConversionParams params, QString sourceFile);
};

#endif // APP_HEADER_H
