#ifndef APPSTATE_H
#define APPSTATE_H

#include <QString>

class AppState
{
    bool empty;
    QString name;
    QString LibrePCBNetlist;
    QString SpiceNetlist;
public:
    ~AppState();
    AppState();
    AppState(const QString &name, const QString &LibrePCBNetlist, const QString &SpiceNetlist);
    bool isEmpty();
    QString getName() const;
    QString getLibrePCBNetlist() const;
    QString getSpiceNetlist() const;
};

#endif // APPSTATE_H
