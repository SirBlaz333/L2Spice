#ifndef APPSTATE_H
#define APPSTATE_H

#include <QString>

class AppState
{
    bool empty;
    QString name;
    QString libreNetlist;
    QString spiceNetlist;
public:
    ~AppState();
    AppState();
    AppState(const QString &name, const QString &libreNetlist, const QString &spiceNetlist);
    bool isEmpty();
    QString getName() const;
    QString getLibreNetlist() const;
    QString getSpiceNetlist() const;
};

#endif // APPSTATE_H
