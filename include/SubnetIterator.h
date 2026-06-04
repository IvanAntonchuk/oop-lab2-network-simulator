#ifndef SUBNETITERATOR_H
#define SUBNETITERATOR_H

#include "NodeIterator.h"
#include <vector>

class SubnetIterator : public NodeIterator {
private:
    std::vector<std::shared_ptr<NetworkNode>> nodes;
    size_t position;

public:
    explicit SubnetIterator(const std::vector<std::shared_ptr<NetworkNode>>& networkNodes);
    bool hasNext() const override;
    std::shared_ptr<NetworkNode> next() override;
};

#endif
