#ifndef NETLISTTEMPORARYSTORAGENODE_H
#define NETLISTTEMPORARYSTORAGENODE_H

#include <QString>

class NetlistTemporaryStorageNode
{
    bool empty;
    QString name;
    QString LibrePCBNetlist;
    QString SpiceNetlist;
public:
    ~NetlistTemporaryStorageNode();
    NetlistTemporaryStorageNode();
    NetlistTemporaryStorageNode(const QString &name, const QString &LibrePCBNetlist, const QString &SpiceNetlist);
    bool isEmpty();
    QString getName() const;
    QString getLibrePCBNetlist() const;
    QString getSpiceNetlist() const;
};

#endif // NETLISTTEMPORARYSTORAGENODE_H
