#include "ServerNode.h"
#include "OnlineState.h"

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
    std::string log = "[Server: " + name + "] ";

    if (state) {
        log += state->handle(this) + " ";
    }

    if (strategy) {
        log += " | " + strategy->route();
    } else {
        log += " | No routing strategy set.";
    }

    log += "\n";
    return log;
}
