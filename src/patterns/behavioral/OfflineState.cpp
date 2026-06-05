#include "OfflineState.h"
#include "ServerNode.h"

std::string OfflineState::handle(ServerNode* node) {
    std::string type = (node->getName().find("Router") != std::string::npos) ? "Router" : "Server";
    return "[OFFLINE] " + type + " is down. Packets rejected";
}
