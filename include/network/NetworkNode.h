#ifndef NETWORKNODE_H
#define NETWORKNODE_H

#include <string>
#include <memory>
#include <vector>

/**
 * @brief Abstract base class representing any network component (Composite & Prototype patterns).
 * * Provides a common interface for individual servers and collections of nodes (Subnets).
 */
class NetworkNode {
protected:
    std::string name;

public:
    explicit NetworkNode(const std::string& nodeName) : name(nodeName) {}
    virtual ~NetworkNode() = default;

    virtual std::string processTraffic() = 0;
    virtual std::string getName() const { return name; }
    virtual void setName(const std::string& newName) { name = newName; }
    virtual bool isOperational() const { return true; }

    /** @brief Creates a deep copy of the node (Prototype pattern). */
    virtual std::shared_ptr<NetworkNode> clone() const = 0;

    virtual void connectTo(std::shared_ptr<NetworkNode> node) {}
    virtual void removeConnection(std::shared_ptr<NetworkNode> node) {}
    virtual void clearConnections() {}
    virtual std::vector<std::shared_ptr<NetworkNode>> getConnections() const { return {}; }
};

#endif
