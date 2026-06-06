#ifndef VISUALEDGE_H
#define VISUALEDGE_H

#include <QObject>
#include <QGraphicsLineItem>
#include <QPen>

class VisualNode;

class VisualEdge : public QObject, public QGraphicsLineItem {
    Q_OBJECT
public:
    VisualEdge(VisualNode* source, VisualNode* target);
    ~VisualEdge();
    void updatePosition();
    void setHighlighted(bool active);

    VisualNode* getSourceNode() const { return sourceNode; }
    VisualNode* getTargetNode() const { return targetNode; }

signals:
    void edgeDeleted(VisualEdge* edge);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    VisualNode* sourceNode;
    VisualNode* targetNode;
};

#endif
