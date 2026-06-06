#include "VisualNode.h"
#include "VisualEdge.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QMenu>
#include <QAction>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

VisualNode::VisualNode(const QString& name) : QGraphicsEllipseItem(0, 0, 70, 70), nodeName(name), isOffline(false), hasFirewall(false), isReachable(false) {
    setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemSendsGeometryChanges);

    textItem = new QGraphicsTextItem(name, this);
    textItem->setDefaultTextColor(Qt::black);
    textItem->setPos(10, 23);

    if (nodeName.startsWith("Router")) {
        isReachable = true;
        setRect(0, 0, 70, 70);
    }
    updateStyle();
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

void VisualNode::setName(const QString& newName) {
    nodeName = newName;
    updateStyle();
}

void VisualNode::setOffline(bool offline) {
    isOffline = offline;
    updateStyle();
}

void VisualNode::setReachable(bool reachable) {
    isReachable = reachable;
    updateStyle();
}

void VisualNode::setFirewall(bool firewall) {
    hasFirewall = firewall;
    updateStyle();
}

void VisualNode::updateStyle() {
    if (isOffline) {
        setBrush(Qt::red);
    } else {
        if (nodeName.startsWith("Router")) {
            setBrush(Qt::cyan);
        } else {
            setBrush(isReachable ? Qt::green : Qt::yellow);
        }
    }

    if (isSelected()) {
        setPen(QPen(Qt::white, 4));
    } else if (hasFirewall) {
        setPen(QPen(Qt::blue, 4));
    } else {
        setPen(QPen(Qt::black, 2));
    }

    if (hasFirewall) {
        textItem->setPlainText("[FW] " + nodeName);
    } else {
        textItem->setPlainText(nodeName);
    }

    update();
}

QVariant VisualNode::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionHasChanged || change == ItemTransformHasChanged) {
        for (VisualEdge* edge : edges) {
            edge->updatePosition();
        }
    }
    if (change == ItemSelectedHasChanged) {
        updateStyle();
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

void VisualNode::contextMenuEvent(QGraphicsSceneContextMenuEvent *event) {
    QList<QGraphicsItem*> selected = scene()->selectedItems();
    if (selected.size() == 1 && selected.first() != this) {
        VisualNode* sourceNode = dynamic_cast<VisualNode*>(selected.first());
        if (sourceNode) {
            QMenu menu;
            QAction* connectAction = menu.addAction("Connect");
            QAction* selectedAction = menu.exec(event->screenPos());
            if (selectedAction == connectAction) {
                emit connectionRequested(sourceNode, this);
            }
        }
    } else {
        QMenu menu;
        QAction* renameAction = menu.addAction("Rename Node");
        QAction* stateAction = menu.addAction(isOffline ? "Turn Online" : "Turn Offline");
        QAction* fwAction = menu.addAction(hasFirewall ? "Remove Firewall" : "Add Firewall");
        QAction* deleteAction = menu.addAction("Delete Node");

        QAction* selectedAction = menu.exec(event->screenPos());
        if (selectedAction == renameAction) emit renameRequested(this);
        else if (selectedAction == stateAction) emit toggleStateRequested(this);
        else if (selectedAction == fwAction) emit toggleFirewallRequested(this);
        else if (selectedAction == deleteAction) emit nodeDeleted(this);
    }
}

void VisualNode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    QStyleOptionGraphicsItem opt = *option;
    opt.state &= ~QStyle::State_Selected;

    QPen currentPen = pen();
    if (hasFirewall) {
        currentPen = QPen(Qt::blue, 4);
    }
    painter->setPen(currentPen);

    painter->setBrush(brush());

    if (nodeName.startsWith("Router")) {
        painter->drawRect(0, 0, 70, 70);
    } else {
        painter->drawEllipse(0, 0, 70, 70);
    }
}
