#ifndef SUBNET_H
#define SUBNET_H

#include "NetworkNode.h"
#include "NodeIterator.h"
#include <vector>
#include <memory>

class Subnet : public NetworkNode {
private:
    std::vector<std::shared_ptr<NetworkNode>> nodes;

public:
    explicit Subnet(const std::string& subnetName);

    void addNode(std::shared_ptr<NetworkNode> node);
    void removeNode(const std::string& nodeName);

    std::string processTraffic() override;
    const std::vector<std::shared_ptr<NetworkNode>>& getNodes() const;

    std::shared_ptr<NetworkNode> clone() const override;

    std::unique_ptr<NodeIterator> createIterator() const;
};

#endif
