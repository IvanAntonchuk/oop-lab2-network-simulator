#include "ServerNode.h"
#include <iostream>

ServerNode::ServerNode(const std::string& nodeName) : NetworkNode(nodeName) {}

void ServerNode::processTraffic() {
    std::cout << "[Server] Processing traffic at: " << name << std::endl;
}
