#include "appstate.h"

QString AppState::getName() const
{
    return name;
}

QString AppState::getLibreNetlist() const
{
    return libreNetlist;
}

QString AppState::getSpiceNetlist() const
{
    return spiceNetlist;
}

AppState::~AppState() {}

AppState::AppState()
{
    name = "none";
    empty = true;
}

AppState::AppState(const QString &name, const QString &libreNetlist, const QString &spiceNetlist)
    : name(name)
    , libreNetlist(libreNetlist)
    , spiceNetlist(spiceNetlist)
{
    empty = false;
}

bool AppState::isEmpty()
{
    return empty;
}
