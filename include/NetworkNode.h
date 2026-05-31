#ifndef NETWORKNODE_H
#define NETWORKNODE_H

#include <string>

class NetworkNode {
protected:
    std::string name;

public:
    explicit NetworkNode(const std::string& nodeName) : name(nodeName) {}
    virtual ~NetworkNode() = default;

    virtual void processTraffic() = 0;

    virtual std::string getName() const { return name; }
};

#endif
