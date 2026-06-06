#include "ToggleStateCommand.h"
#include "VisualNode.h"
#include "ServerNode.h"
#include "OfflineState.h"
#include "OnlineState.h"

ToggleStateCommand::ToggleStateCommand(VisualNode* vNode, std::shared_ptr<ServerNode> sNode, bool prevOffline, std::function<void()> cb)
    : visualNode(vNode), serverNode(sNode), wasOffline(prevOffline), updateCallback(cb) {}

void ToggleStateCommand::execute() {
    visualNode->setOffline(!wasOffline);
    if (!wasOffline) {
        serverNode->changeState(std::make_shared<OfflineState>());
    } else {
        serverNode->changeState(std::make_shared<OnlineState>());
    }
    updateCallback();
}

void ToggleStateCommand::undo() {
    visualNode->setOffline(wasOffline);
    if (wasOffline) {
        serverNode->changeState(std::make_shared<OfflineState>());
    } else {
        serverNode->changeState(std::make_shared<OnlineState>());
    }
    updateCallback();
}
