#include "DeleteNodeCommand.h"
#include "VisualNode.h"
#include "ServerNode.h"
#include "VisualEdge.h"
#include <QGraphicsScene>

DeleteNodeCommand::DeleteNodeCommand(std::map<VisualNode*, std::shared_ptr<ServerNode>>& nodesMap,
                                     QGraphicsScene* scene,
                                     VisualNode* vNode,
                                     std::shared_ptr<ServerNode> sNode,
                                     QList<VisualEdge*> edges,
                                     std::function<void()> cb)
    : coreNodes(nodesMap), graphicsScene(scene), visualNode(vNode), serverNode(sNode),
    connectedEdges(edges), updateCallback(cb) {}

void DeleteNodeCommand::execute() {
    for (VisualEdge* edge : connectedEdges) {
        graphicsScene->removeItem(edge);
    }
    graphicsScene->removeItem(visualNode);
    coreNodes.erase(visualNode);
    updateCallback();
}

void DeleteNodeCommand::undo() {
    coreNodes[visualNode] = serverNode;
    graphicsScene->addItem(visualNode);
    for (VisualEdge* edge : connectedEdges) {
        graphicsScene->addItem(edge);
    }
    updateCallback();
}
