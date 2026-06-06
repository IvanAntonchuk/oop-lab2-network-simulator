#ifndef ADDNODECOMMAND_H
#define ADDNODECOMMAND_H

#include "SimulationCommand.h"
#include <map>
#include <memory>
#include <functional>

class VisualNode;
class ServerNode;
class QGraphicsScene;

class AddNodeCommand : public ICommand {
public:
    AddNodeCommand(std::map<VisualNode*, std::shared_ptr<ServerNode>>& nodesMap,
                   QGraphicsScene* scene,
                   VisualNode* vNode,
                   std::shared_ptr<ServerNode> sNode,
                   int* sCounter, int oldSCounter,
                   int* rCounter, int oldRCounter,
                   std::function<void()> cb);
    void execute() override;
    void undo() override;

private:
    std::map<VisualNode*, std::shared_ptr<ServerNode>>& coreNodes;
    QGraphicsScene* graphicsScene;
    VisualNode* visualNode;
    std::shared_ptr<ServerNode> serverNode;
    int* serverCounter;
    int savedServerCounter;
    int* routerCounter;
    int savedRouterCounter;
    std::function<void()> updateCallback;
};

#endif
