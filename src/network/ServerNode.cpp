#include "ServerNode.h"
#include "OnlineState.h"
#include <algorithm>

ServerNode::ServerNode(const std::string& nodeName)
    : NetworkNode(nodeName), strategy(nullptr), state(std::make_shared<OnlineState>()) {}

void ServerNode::setStrategy(std::shared_ptr<RoutingStrategy> newStrategy) {
    strategy = newStrategy;
}

void ServerNode::changeState(std::shared_ptr<NodeState> newState) {
    if (newState) {
        state = newState;
    }
}

std::string ServerNode::processTraffic() {
    std::string log = "[Node: " + name + "] ";
    if (state) log += state->handle(this) + " ";
    if (strategy) log += " | " + strategy->route();
    else log += " | No routing strategy set.";
    log += "\n";
    return log;
}

bool ServerNode::isOperational() const {
    return state ? state->isOperational() : false;
}

std::shared_ptr<NetworkNode> ServerNode::clone() const {
    auto cloned = std::make_shared<ServerNode>(name + "_clone");
    cloned->setStrategy(strategy);
    cloned->changeState(state);
    return cloned;
}

void ServerNode::connectTo(std::shared_ptr<NetworkNode> node) {
    for (auto& conn : connections) {
        if (conn->getName() == node->getName()) return;
    }
    connections.push_back(node);
}

void ServerNode::removeConnection(std::shared_ptr<NetworkNode> node) {
    connections.erase(std::remove_if(connections.begin(), connections.end(),
                                     [&node](const std::shared_ptr<NetworkNode>& n) { return n->getName() == node->getName(); }),
                      connections.end());
}

void ServerNode::clearConnections() {
    connections.clear();
}

std::vector<std::shared_ptr<NetworkNode>> ServerNode::getConnections() const {
    return connections;
}
