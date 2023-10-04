#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

class Signal
{
private:
    std::string uuid;
    std::string name;

public:
    Signal(std::string uuid, std::string name);
    ~Signal();
    std::string getUUID();
    std::string getName();
};

#endif // SIGNAL_H
