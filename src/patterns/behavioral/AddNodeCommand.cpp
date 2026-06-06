#include "AddNodeCommand.h"
#include "VisualNode.h"
#include "ServerNode.h"
#include <QGraphicsScene>

AddNodeCommand::AddNodeCommand(std::map<VisualNode*, std::shared_ptr<ServerNode>>& nodesMap,
                               QGraphicsScene* scene,
                               VisualNode* vNode,
                               std::shared_ptr<ServerNode> sNode,
                               int* sCounter, int oldSCounter,
                               int* rCounter, int oldRCounter,
                               std::function<void()> cb)
    : coreNodes(nodesMap), graphicsScene(scene), visualNode(vNode), serverNode(sNode),
    serverCounter(sCounter), savedServerCounter(oldSCounter),
    routerCounter(rCounter), savedRouterCounter(oldRCounter),
    updateCallback(cb) {}

void AddNodeCommand::execute() {
    coreNodes[visualNode] = serverNode;
    graphicsScene->addItem(visualNode);
    updateCallback();
}

void AddNodeCommand::undo() {
    graphicsScene->removeItem(visualNode);
    coreNodes.erase(visualNode);
    *serverCounter = savedServerCounter;
    *routerCounter = savedRouterCounter;
    updateCallback();
}
