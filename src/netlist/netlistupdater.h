#ifndef NETLISTUPDATER_H
#define NETLISTUPDATER_H

#include <QString>


class NetlistUpdater
{
private:
    static const QRegularExpression componentRegex;
    static const QRegularExpression nameRegex;
    static const QRegularExpression paramRegex;
    static const QRegularExpression attributeRegex;

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
public:
    NetlistUpdater();
    ~NetlistUpdater();
    QString updateNetlist(QString textToUpdate, QString oldVersion, QString newVersion);
};

#endif // NETLISTUPDATER_H
