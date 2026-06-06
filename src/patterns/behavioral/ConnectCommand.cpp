#include "ConnectCommand.h"
#include "VisualEdge.h"
#include <QGraphicsScene>

ConnectCommand::ConnectCommand(QGraphicsScene* scene, VisualEdge* e, std::function<void()> cb)
    : graphicsScene(scene), edge(e), updateCallback(cb) {}

void ConnectCommand::execute() {
    graphicsScene->addItem(edge);
    updateCallback();
}

void ConnectCommand::undo() {
    graphicsScene->removeItem(edge);
    updateCallback();
}
