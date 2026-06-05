#include "OnlineState.h"
#include "ServerNode.h"

std::string OnlineState::handle(ServerNode* node) {
    std::string type = (node->getName().find("Router") != std::string::npos) ? "Router" : "Server";
    return "[ONLINE] " + type + " is accepting traffic";
}
