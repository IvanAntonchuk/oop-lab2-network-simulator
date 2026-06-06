#ifndef VISUALNODE_H
#define VISUALNODE_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QPen>

class VisualEdge;

class VisualNode : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
public:
    VisualNode(const QString& name);
    void addEdge(VisualEdge* edge);
    void removeEdge(VisualEdge* edge);
    QString getName() const;
    void setName(const QString& newName);
    QList<VisualEdge*> getEdges() const { return edges; }

    bool getIsOffline() const { return isOffline; }
    bool getHasFirewall() const { return hasFirewall; }
    bool getIsReachable() const { return isReachable; }

    void setOffline(bool offline);
    void setFirewall(bool firewall);
    void setReachable(bool reachable);

signals:
    void connectionRequested(VisualNode* source, VisualNode* target);
    void nodeDeleted(VisualNode* node);
    void renameRequested(VisualNode* node);
    void toggleStateRequested(VisualNode* node);
    void toggleFirewallRequested(VisualNode* node);
    void strategyChangedRequested(VisualNode* node, int type);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    void updateStyle();

    QString nodeName;
    QList<VisualEdge*> edges;
    QGraphicsTextItem* textItem;
    bool isOffline;
    bool hasFirewall;
    bool isReachable;
};

#endif
