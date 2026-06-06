#ifndef DISCONNECTCOMMAND_H
#define DISCONNECTCOMMAND_H

#include "SimulationCommand.h"
#include <functional>

class QGraphicsScene;
class VisualEdge;

class DisconnectCommand : public ICommand {
public:
    DisconnectCommand(QGraphicsScene* scene, VisualEdge* e, std::function<void()> cb);
    void execute() override;
    void undo() override;
private:
    QGraphicsScene* graphicsScene;
    VisualEdge* edge;
    std::function<void()> updateCallback;
};

#endif
