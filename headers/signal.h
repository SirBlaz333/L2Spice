#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

class Signal
{
private:
    std::string uuid;
    std::string netUuid;

public:
    Signal(const std::string &uuid, const std::string &netUuid);
    ~Signal();

    std::string getUuid() const;
    std::string getNetUuid() const;
};

#endif // SIGNAL_H
