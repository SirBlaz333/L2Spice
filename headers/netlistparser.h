#ifndef NETLISTPARSER_H
#define NETLISTPARSER_H

#include <headers/circuit.h>
#include <iostream>
#include <QMap>
#include <QSharedPointer>
#include <bits/unique_ptr.h>


class NetlistParser
{
private:
    QMap<QString, std::function<QSharedPointer<Element>()>> elementFactory;
    QString::iterator currentCharacter;
    QMap<QString, QSharedPointer<Element>> elementMap;

    QString nextWord();
    QString nextDataInQuotes();
    void parseComponents(QString::iterator last);
    void parseComponent(QString parentUuid,  QString::iterator last);
    Element* createNewElement(QString name, QString uuid);
    void parseElement(QString parentUuid, QString::iterator last);
public:
    NetlistParser();
    ~NetlistParser();
    Circuit parseLibreNotation(QString input);
};

#endif // NETLISTPARSER_H
