#include "Subnet.h"
#include "SubnetIterator.h"
#include <algorithm>
#include <set>
#include <queue>

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
    std::set<std::string> visited;
    std::queue<std::shared_ptr<NetworkNode>> queue;

    for (const auto& node : nodes) {
        if (node->getName().find("Router") != std::string::npos) {
            queue.push(node);
            visited.insert(node->getName());
        }
    }

    if (queue.empty()) {
        return log + "    [Error] No Router found! Traffic has no entry point.\n";
    }

    while (!queue.empty()) {
        auto curr = queue.front();
        queue.pop();
        log += "    " + curr->processTraffic();

        for (const auto& neighbor : curr->getConnections()) {
            if (visited.find(neighbor->getName()) == visited.end()) {
                visited.insert(neighbor->getName());
                queue.push(neighbor);
            }
        }
    }

    for (const auto& node : nodes) {
        if (visited.find(node->getName()) == visited.end()) {
            log += "    [Node: " + node->getName() + "] [ISOLATED] Not connected to the active network.\n";
        }
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
