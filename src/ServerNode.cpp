#include "ServerNode.h"

ServerNode::ServerNode(const std::string& nodeName) : NetworkNode(nodeName) {}

std::string ServerNode::processTraffic() {
    return "[Server] Processing traffic at: " + name + "\n";
}
