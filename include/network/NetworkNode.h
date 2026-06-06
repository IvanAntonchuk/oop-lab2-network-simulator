#ifndef NETWORKNODE_H
#define NETWORKNODE_H

#include <string>
#include <memory>
#include <vector>

class NetworkNode {
protected:
    std::string name;

public:
    explicit NetworkNode(const std::string& nodeName) : name(nodeName) {}
    virtual ~NetworkNode() = default;

    virtual std::string processTraffic() = 0;
    virtual std::string getName() const { return name; }
    virtual void setName(const std::string& newName) { name = newName; }

    virtual std::shared_ptr<NetworkNode> clone() const = 0;

    virtual void connectTo(std::shared_ptr<NetworkNode> node) {}
    virtual void removeConnection(std::shared_ptr<NetworkNode> node) {}
    virtual std::vector<std::shared_ptr<NetworkNode>> getConnections() const { return {}; }
};

#endif
