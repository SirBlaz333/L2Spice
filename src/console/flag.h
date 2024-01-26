#ifndef FLAG_H
#define FLAG_H

#include <QString>


class Flag
{
    std::string flag;
    std::string alias;

public:
    Flag(const std::string &flag, const std::string &alias);
    std::string getFlag() const;
    std::string getAlias() const;
};

#endif // FLAG_H
