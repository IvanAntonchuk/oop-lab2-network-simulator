#include "SubnetIterator.h"

SubnetIterator::SubnetIterator(const std::vector<std::shared_ptr<NetworkNode>>& networkNodes)
    : nodes(networkNodes), currentIndex(0) {}

bool SubnetIterator::hasNext() const {
    return currentIndex < nodes.size();
}

std::shared_ptr<NetworkNode> SubnetIterator::next() {
    if (hasNext()) {
        return nodes[currentIndex++];
    }
    return nullptr;
}
