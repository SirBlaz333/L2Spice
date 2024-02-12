#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

#include <QSet>

class GlobalVariables
{
public:
    const static std::string VERSION;
    const static int SIMULATOR_VERSION_JSIM;
    const static int SIMULATOR_VERSION_JOSIM;
    const static QSet<QString> JSIM_MODEL_ATTRIBUTES;
    const static QSet<QString> JOSIM_MODEL_ATTRIBUTES;
};

#endif // GLOBAL_VARIABLES_H
