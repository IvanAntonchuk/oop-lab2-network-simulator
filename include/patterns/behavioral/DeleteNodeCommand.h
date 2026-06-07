#ifndef DELETENODECOMMAND_H
#define DELETENODECOMMAND_H

#include "SimulationCommand.h"
#include <map>
#include <memory>
#include <QList>
#include <functional>

class VisualNode;
class ServerNode;
class QGraphicsScene;
class VisualEdge;

/**
 * @brief Command to remove a node and all its connected edges from the network.
 */
class DeleteNodeCommand : public ICommand {
public:
    DeleteNodeCommand(std::map<VisualNode*, std::shared_ptr<ServerNode>>& nodesMap,
                      QGraphicsScene* scene,
                      VisualNode* vNode,
                      std::shared_ptr<ServerNode> sNode,
                      QList<VisualEdge*> edges,
                      std::function<void()> cb);
    void execute() override;
    void undo() override;

private:
    std::map<VisualNode*, std::shared_ptr<ServerNode>>& coreNodes;
    QGraphicsScene* graphicsScene;
    VisualNode* visualNode;
    std::shared_ptr<ServerNode> serverNode;
    QList<VisualEdge*> connectedEdges;
    std::function<void()> updateCallback;
};

#endif
