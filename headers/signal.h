#ifndef SIGNAL_H
#define SIGNAL_H

#include <string>

class Signal
{
private:
    std::string uuid;
    std::string netUuid;

public:
    Signal();
    ~Signal();

    std::string getUuid() const;
    void setUuid(const std::string &newUuid);
    std::string getNetUuid() const;
    void setNetUuid(const std::string &newNetUuid);
};

#endif // SIGNAL_H
