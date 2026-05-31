#ifndef SERVERNODE_H
#define SERVERNODE_H

#include "NetworkNode.h"

class ServerNode : public NetworkNode {
public:
    explicit ServerNode(const std::string& nodeName);
    void processTraffic() override;
};

#endif
