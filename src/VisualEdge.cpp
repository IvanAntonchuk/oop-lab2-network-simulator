#include "VisualEdge.h"
#include "VisualNode.h"
#include <QPen>
#include <QMenu>
#include <QAction>
#include <QGraphicsSceneContextMenuEvent>
#include <QStyleOptionGraphicsItem>

VisualEdge::VisualEdge(VisualNode* source, VisualNode* target)
    : sourceNode(source), targetNode(target) {
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    QPen pen(Qt::black, 3);
    setPen(pen);
    setZValue(-1);
    sourceNode->addEdge(this);
    targetNode->addEdge(this);
    updatePosition();
}

VisualEdge::~VisualEdge() {
    sourceNode->removeEdge(this);
    targetNode->removeEdge(this);
}

void VisualEdge::updatePosition() {
    QPointF p1 = sourceNode->pos() + QPointF(35, 35);
    QPointF p2 = targetNode->pos() + QPointF(35, 35);
    setLine(QLineF(p1, p2));
}

void VisualEdge::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    QMenu menu;
    QAction* deleteAction = menu.addAction("Розірвати з'єднання");
    QAction* selectedAction = menu.exec(event->screenPos());
    if (selectedAction == deleteAction) {
        emit edgeDeleted(this);
    }
}

QVariant VisualEdge::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemSelectedHasChanged) {
        QPen currentPen = isSelected() ? QPen(Qt::white, 4) : QPen(Qt::black, 3);
        setPen(currentPen);
    }
    return QGraphicsLineItem::itemChange(change, value);
}

void VisualEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QStyleOptionGraphicsItem opt = *option;
    opt.state &= ~QStyle::State_Selected;
    QGraphicsLineItem::paint(painter, &opt, widget);
}
