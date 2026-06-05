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

signals:
    void connectionRequested(VisualNode* source, VisualNode* target);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QString nodeName;
    QList<VisualEdge*> edges;
};

#endif
