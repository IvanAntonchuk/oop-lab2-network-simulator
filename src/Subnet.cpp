#include "Subnet.h"
#include "SubnetIterator.h"
#include <algorithm>

Subnet::Subnet(const std::string& subnetName) : NetworkNode(subnetName) {}

void Subnet::addNode(std::shared_ptr<NetworkNode> node) {
    if (node) nodes.push_back(node);
}

void Subnet::removeNode(const std::string& nodeName) {
    nodes.erase(std::remove_if(nodes.begin(), nodes.end(),
                               [&nodeName](const std::shared_ptr<NetworkNode>& node) {
                                   return node->getName() == nodeName;
                               }), nodes.end());
}

std::string Subnet::processTraffic() {
    std::string log = "[Subnet] Routing traffic in subnet: " + name + "\n";
    for (const auto& node : nodes) {
        log += "    " + node->processTraffic();
    }
    return log;
}

const std::vector<std::shared_ptr<NetworkNode>>& Subnet::getNodes() const {
    return nodes;
}

std::shared_ptr<NetworkNode> Subnet::clone() const {
    auto cloned = std::make_shared<Subnet>(name + "_clone");
    for (const auto& node : nodes) {
        cloned->addNode(node->clone());
    }
    return cloned;
}

std::unique_ptr<NodeIterator> Subnet::createIterator() const {
    return std::make_unique<SubnetIterator>(nodes);
}
