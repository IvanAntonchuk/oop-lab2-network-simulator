#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#include "NetworkNode.h"
#include <memory>

class NodeIterator {
public:
    virtual ~NodeIterator() = default;
    virtual bool hasNext() const = 0;
    virtual std::shared_ptr<NetworkNode> next() = 0;
};

#endif
