#include "../headers/net.h"

Net::Net(bool autoMode, const NetClass &netclass, const std::string &uuid, const std::string &name)
    : NetClass(uuid, name)
    , autoMode(autoMode)
    , netclass(netclass)
{}

Net::~Net() {}
