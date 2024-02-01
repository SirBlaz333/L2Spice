#include "app_state.h"

QString AppState::getSpiceSourceFile() const
{
    return spiceSourceFile;
}

QString AppState::getLibreSourceFile() const
{
    return libreSourceFile;
}

QString AppState::getSpiceNetlist() const
{
    return spiceNetlist;
}

QString AppState::getLibreNetlist() const
{
    return libreNetlist;
}

QString AppState::getName() const
{
    return name;
}

bool AppState::isEmpty() const
{
    return empty;
}

void AppState::setLibreSourceFile(const QString &newLibreSourceFile)
{
    libreSourceFile = newLibreSourceFile;
}

void AppState::setSpiceSourceFile(const QString &newSpiceSourceFile)
{
    spiceSourceFile = newSpiceSourceFile;
}

AppState::AppState()
{
    empty = true;
    name = "none";
}

AppState::AppState(const QString &name,
                   const QString &libreNotation,
                   const QString &spiceNotation,
                   const QString &libreSourceFile,
                   const QString &spiceSourceFile)
    : name(name)
    , libreNetlist(libreNotation)
    , spiceNetlist(spiceNotation)
    , libreSourceFile(libreSourceFile)
    , spiceSourceFile(spiceSourceFile)
{
    empty = false;
}
