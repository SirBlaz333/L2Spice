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

NetlistTemporaryStorageNode::NetlistTemporaryStorageNode()
{
    empty = true;
}

NetlistTemporaryStorageNode::NetlistTemporaryStorageNode(const QString &name,
                                                         const QString &LibrePCBNetlist,
                                                         const QString &SpiceNetlist)
    : name(name)
    , LibrePCBNetlist(LibrePCBNetlist)
    , SpiceNetlist(SpiceNetlist)
{
    empty = false;
}

bool NetlistTemporaryStorageNode::isEmpty()
{
    return empty;
}
