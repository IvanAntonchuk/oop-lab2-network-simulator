#include "DisconnectCommand.h"
#include "VisualEdge.h"
#include <QGraphicsScene>

DisconnectCommand::DisconnectCommand(QGraphicsScene* scene, VisualEdge* e, std::function<void()> cb)
    : graphicsScene(scene), edge(e), updateCallback(cb) {}

void DisconnectCommand::execute() {
    graphicsScene->removeItem(edge);
    updateCallback();
}

void DisconnectCommand::undo() {
    graphicsScene->addItem(edge);
    updateCallback();
}
