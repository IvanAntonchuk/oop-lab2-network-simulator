#ifndef SERVERNODE_H
#define SERVERNODE_H

#include "NetworkNode.h"
#include "RoutingStrategy.h"
#include "NodeState.h"
#include <memory>

class ServerNode : public NetworkNode {
private:
    std::shared_ptr<RoutingStrategy> strategy;
    std::shared_ptr<NodeState> state;

public:
    explicit ServerNode(const std::string& nodeName);

    void setStrategy(std::shared_ptr<RoutingStrategy> newStrategy);
    void changeState(std::shared_ptr<NodeState> newState);

    std::string processTraffic() override;

    std::shared_ptr<NetworkNode> clone() const override;
};

#endif
