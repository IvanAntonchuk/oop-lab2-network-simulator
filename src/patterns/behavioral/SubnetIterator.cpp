#include "SubnetIterator.h"

SubnetIterator::SubnetIterator(const std::vector<std::shared_ptr<NetworkNode>>& networkNodes)
    : nodes(networkNodes), position(0) {}

bool SubnetIterator::hasNext() const {
    return position < nodes.size();
}

std::shared_ptr<NetworkNode> SubnetIterator::next() {
    if (hasNext()) {
        return nodes[position++];
    }
    return nullptr;
}
