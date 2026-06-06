#ifndef CONNECTCOMMAND_H
#define CONNECTCOMMAND_H

#include "SimulationCommand.h"
#include <functional>

class QGraphicsScene;
class VisualEdge;

class ConnectCommand : public ICommand {
public:
    ConnectCommand(QGraphicsScene* scene, VisualEdge* e, std::function<void()> cb);
    void execute() override;
    void undo() override;
private:
    QGraphicsScene* graphicsScene;
    VisualEdge* edge;
    std::function<void()> updateCallback;
};

#endif
