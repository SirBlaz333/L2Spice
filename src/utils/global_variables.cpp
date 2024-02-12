#include "global_variables.h"

const std::string GlobalVariables::VERSION = "1.0.0";
const int GlobalVariables::SIMULATOR_VERSION_JSIM = 0;
const int GlobalVariables::SIMULATOR_VERSION_JOSIM = 1;
const QSet<QString> GlobalVariables::JSIM_MODEL_ATTRIBUTES
    = {"RTYPE", "CCT", "VG", "DELV", "ICON", "R0", "RN", "CAP", "ICRIT"};
const QSet<QString> GlobalVariables::JOSIM_MODEL_ATTRIBUTES
    = {"RTYPE", "VG", "DELV", "R0", "RN", "CAP", "ICRIT", "T", "TC", "D", "ICFCT", "PHI", "CPR"};
