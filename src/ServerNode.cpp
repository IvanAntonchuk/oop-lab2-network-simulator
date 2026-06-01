#include "ServerNode.h"

ServerNode::ServerNode(const std::string& nodeName)
    : NetworkNode(nodeName), strategy(nullptr) {}

void ServerNode::setStrategy(std::shared_ptr<RoutingStrategy> newStrategy) {
    strategy = newStrategy;
}

std::string ServerNode::processTraffic() {
    std::string log = "[Server] Processing traffic at: " + name;

    if (strategy) {
        log += " | " + strategy->route();
    } else {
        log += " | No routing strategy set.";
    }

    log += "\n";
    return log;
}
