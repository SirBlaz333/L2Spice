#ifndef APP_HEADER_H
#define APP_HEADER_H

#include <QString>

#include <src/conversion/data/conversion_params.h>
/**
 * AppHeader is used to create a header for the conversion. Header can
 * contain current time, name of the LibrePCB project from which was the
 * conversion made and for what simulator the SPICE netlist was created.
 */
class AppHeader
{
public:
    /**
     * Creates the header.
     *
     * @param params - instance of ConversionParams class, that contain desired parameters for the conversion.
     * @param sourceFile - the location of the LibrePCB circuit file. It is used to determine the project, if it exists.
     * @return header for the conversion.
     */
    QString getHeader(ConversionParams params, QString sourceFile);
};

#endif // APP_HEADER_H
