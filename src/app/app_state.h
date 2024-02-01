#ifndef APP_STATE_H
#define APP_STATE_H

#include <qstring.h>

class AppState
{
    bool empty;
    QString name;
    QString libreNetlist;
    QString spiceNetlist;
    QString libreSourceFile;
    QString spiceSourceFile;

public:
    AppState();
    AppState(const QString &name,
             const QString &libreNotation,
             const QString &spiceNotation,
             const QString &libreSourceFile = QString(),
             const QString &spiceSourceFile = QString());

    QString getSpiceSourceFile() const;
    QString getLibreSourceFile() const;
    QString getSpiceNetlist() const;
    QString getLibreNetlist() const;
    QString getName() const;
    bool isEmpty() const;
    void setLibreSourceFile(const QString &newLibreSourceFile);
    void setSpiceSourceFile(const QString &newSpiceSourceFile);
};

#endif // APP_STATE_H
