#include "VisualNode.h"
#include "VisualEdge.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMenu>
#include <QAction>
#include <QStyleOptionGraphicsItem>

VisualNode::VisualNode(const QString& name) : QGraphicsEllipseItem(0, 0, 70, 70), nodeName(name) {
    setBrush(Qt::green);
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);
    QPen pen(Qt::black, 2);
    setPen(pen);

    QGraphicsTextItem* text = new QGraphicsTextItem(name, this);
    text->setDefaultTextColor(Qt::black);
    text->setPos(10, 23);
}

void VisualNode::addEdge(VisualEdge* edge) {
    edges.append(edge);
}

void VisualNode::removeEdge(VisualEdge* edge) {
    edges.removeAll(edge);
}

QString VisualNode::getName() const {
    return nodeName;
}

QVariant VisualNode::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionHasChanged || change == ItemTransformHasChanged) {
        for (VisualEdge* edge : edges) {
            edge->updatePosition();
        }
    }
    if (change == ItemSelectedHasChanged) {
        QPen pen = isSelected() ? QPen(Qt::white, 4) : QPen(Qt::black, 2);
        setPen(pen);
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

void VisualNode::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    QList<QGraphicsItem*> selected = scene()->selectedItems();
    if (selected.size() == 1 && selected.first() != this) {
        VisualNode* sourceNode = dynamic_cast<VisualNode*>(selected.first());
        if (sourceNode) {
            QMenu menu;
            QAction* connectAction = menu.addAction("З'єднати");
            QAction* selectedAction = menu.exec(event->screenPos());
            if (selectedAction == connectAction) {
                emit connectionRequested(sourceNode, this);
            }
        }
    }
}

void VisualNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QStyleOptionGraphicsItem opt = *option;
    opt.state &= ~QStyle::State_Selected;
    QGraphicsEllipseItem::paint(painter, &opt, widget);
}
