#ifndef SERVERNODE_H
#define SERVERNODE_H

#include "NetworkNode.h"
#include "RoutingStrategy.h"
#include <memory>

class ServerNode : public NetworkNode {
private:
    std::shared_ptr<RoutingStrategy> strategy;

public:
    explicit ServerNode(const std::string& nodeName);

    void setStrategy(std::shared_ptr<RoutingStrategy> newStrategy);

    std::string processTraffic() override;
};

#endif
