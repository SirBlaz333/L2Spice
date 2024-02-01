#ifndef LIBRENETLISTUPDATER_H
#define LIBRENETLISTUPDATER_H

#include <QString>


class LibreNetlistUpdater
{
private:
    int simulatorVersion = 1;
    QString getNewUnit(QString param, QString attribute);
    QString getNewAttribute(QString attribute, QString number, QString unit);
    QMap<QString, QString> getComponents(QString textToUpdate);
    QString updateParameter(QString textToUpdate,
                            QString *component,
                            QString param,
                            QString attribute);
    QString update(QString textToUpdate,
                   QString params,
                   QMap<QString, QString> componentsMap);
    QString removeSubcircuitImports(QString param);
public:
    LibreNetlistUpdater();
    ~LibreNetlistUpdater();
    void setSimulatorVersion(int version);
    QString updateNetlist(QString textToUpdate, QString oldVersion, QString newVersion);
};

#endif // LIBRENETLISTUPDATER_H
