#include "global_variables.h"

int SIMULATOR_VERSION_JSIM = 0;
int SIMULATOR_VERSION_JOSIM = 1;
QSet<QString> JSIM_MODEL_ATTRIBUTES
    = {"RTYPE", "CCT", "VG", "DELV", "ICON", "R0", "RN", "CAP", "ICRIT"};
QSet<QString> JOSIM_MODEL_ATTRIBUTES
    = {"RTYPE", "VG", "DELV", "R0", "RN", "CAP", "ICRIT", "T", "TC", "D", "ICFCT", "PHI", "CPR"};
