#include "appstate.h"

QString AppState::getName() const
{
    return name;
}

QString AppState::getLibrePCBNetlist() const
{
    return LibrePCBNetlist;
}

QString AppState::getSpiceNetlist() const
{
    return SpiceNetlist;
}

AppState::~AppState() {}

AppState::AppState()
{
    empty = true;
}

AppState::AppState(const QString &name, const QString &LibrePCBNetlist, const QString &SpiceNetlist)
    : name(name)
    , LibrePCBNetlist(LibrePCBNetlist)
    , SpiceNetlist(SpiceNetlist)
{
    empty = false;
}

bool AppState::isEmpty()
{
    return empty;
}
