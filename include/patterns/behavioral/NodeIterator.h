#ifndef NODEITERATOR_H
#define NODEITERATOR_H

#include "NetworkNode.h"
#include <memory>

/**
 * @brief Interface for sequentially accessing elements of a composite network (Iterator pattern).
 * * Provides a standard way to traverse through nodes in a Subnet without
 * exposing its internal underlying representation.
 */
class NodeIterator {
public:
    virtual ~NodeIterator() = default;

    /** @brief Checks if there are more nodes in the iteration. */
    virtual bool hasNext() const = 0;

    /** @brief Retrieves the next node in the iteration sequence. */
    virtual std::shared_ptr<NetworkNode> next() = 0;
};

#endif
