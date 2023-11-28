#ifndef NETLISTTEMPORARYSTORAGENODE_H
#define NETLISTTEMPORARYSTORAGENODE_H

#include <QString>

class NetlistTemporaryStorageNode
{
    QString name;
    QString LibrePCBNetlist;
    QString SpiceNetlist;
public:
    ~NetlistTemporaryStorageNode();
    NetlistTemporaryStorageNode(const QString &name, const QString &LibrePCBNetlist, const QString &SpiceNetlist);

    QString getName() const;
    QString getLibrePCBNetlist() const;
    QString getSpiceNetlist() const;
};

#endif // NETLISTTEMPORARYSTORAGENODE_H
