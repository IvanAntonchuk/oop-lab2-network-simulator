#ifndef SUBNETITERATOR_H
#define SUBNETITERATOR_H

#include "NodeIterator.h"
#include "NetworkNode.h"
#include <vector>
#include <memory>

/**
 * @brief Concrete iterator for traversing nodes within a Subnet.
 */
class SubnetIterator : public NodeIterator {
public:
    explicit SubnetIterator(const std::vector<std::shared_ptr<NetworkNode>>& networkNodes);
    bool hasNext() const override;
    std::shared_ptr<NetworkNode> next() override;

private:
    std::vector<std::shared_ptr<NetworkNode>> nodes;
    size_t currentIndex;
};

#endif
