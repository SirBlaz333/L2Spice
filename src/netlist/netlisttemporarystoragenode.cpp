#include "netlisttemporarystoragenode.h"

QString NetlistTemporaryStorageNode::getName() const
{
    return name;
}

QString NetlistTemporaryStorageNode::getLibrePCBNetlist() const
{
    return LibrePCBNetlist;
}

QString NetlistTemporaryStorageNode::getSpiceNetlist() const
{
    return SpiceNetlist;
}

NetlistTemporaryStorageNode::~NetlistTemporaryStorageNode() {}

NetlistTemporaryStorageNode::NetlistTemporaryStorageNode(const QString &name,
                                                         const QString &LibrePCBNetlist,
                                                         const QString &SpiceNetlist)
    : name(name)
    , LibrePCBNetlist(LibrePCBNetlist)
    , SpiceNetlist(SpiceNetlist)
{}
