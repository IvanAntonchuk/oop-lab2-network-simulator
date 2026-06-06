#ifndef SERVERNODE_H
#define SERVERNODE_H

#include "NetworkNode.h"
#include "RoutingStrategy.h"
#include "NodeState.h"
#include <memory>
#include <vector>

class ServerNode : public NetworkNode {
private:
    std::shared_ptr<RoutingStrategy> strategy;
    std::shared_ptr<NodeState> state;
    std::vector<std::weak_ptr<NetworkNode>> connections;

public:
    explicit ServerNode(const std::string& nodeName);

    void setStrategy(std::shared_ptr<RoutingStrategy> newStrategy);
    void changeState(std::shared_ptr<NodeState> newState);

    std::string processTraffic() override;
    bool isOperational() const override;
    std::shared_ptr<NetworkNode> clone() const override;

    void connectTo(std::shared_ptr<NetworkNode> node) override;
    void removeConnection(std::shared_ptr<NetworkNode> node) override;
    void clearConnections() override;
    std::vector<std::shared_ptr<NetworkNode>> getConnections() const override;
    std::shared_ptr<RoutingStrategy> getStrategy() const { return strategy; }
};

#endif
