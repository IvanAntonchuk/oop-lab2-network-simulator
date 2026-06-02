#ifndef NETWORKNODE_H
#define NETWORKNODE_H

#include <string>
#include <memory>

class NetworkNode {
protected:
    std::string name;

public:
    explicit NetworkNode(const std::string& nodeName) : name(nodeName) {}
    virtual ~NetworkNode() = default;

    virtual std::string processTraffic() = 0;
    virtual std::string getName() const { return name; }

    virtual std::shared_ptr<NetworkNode> clone() const = 0;
};

#endif
