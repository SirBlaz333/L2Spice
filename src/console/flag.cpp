#include "flag.h"

Flag::Flag(const std::string &flag, const std::string &alias)
    : flag(flag)
    , alias(alias)
{}

std::string Flag::getFlag() const
{
    return flag;
}

std::string Flag::getAlias() const
{
    return alias;
}
