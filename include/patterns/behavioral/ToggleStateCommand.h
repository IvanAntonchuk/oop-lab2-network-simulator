#ifndef TOGGLESTATECOMMAND_H
#define TOGGLESTATECOMMAND_H

#include "SimulationCommand.h"
#include <memory>
#include <functional>

class VisualNode;
class ServerNode;

class ToggleStateCommand : public ICommand {
public:
    ToggleStateCommand(VisualNode* vNode, std::shared_ptr<ServerNode> sNode, bool prevOffline, std::function<void()> cb);
    void execute() override;
    void undo() override;
private:
    VisualNode* visualNode;
    std::shared_ptr<ServerNode> serverNode;
    bool wasOffline;
    std::function<void()> updateCallback;
};

#endif
