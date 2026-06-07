#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QDockWidget>
#include <QScrollArea>
#include <QKeyEvent>
#include <map>
#include "NetworkBuilder.h"
#include "NetworkNode.h"
#include "ServerNode.h"
#include "VisualNode.h"
#include "VisualEdge.h"

class QLabel;
class DashboardObserver;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Structure to store information about an active highlighted path in the network.
 */
struct ActivePath {
    int id;                                           ///< Unique identifier for the path.
    QString targetName;                               ///< Name of the target node.
    QString strategyName;                             ///< Name of the routing strategy used.
    std::vector<std::shared_ptr<NetworkNode>> pathNodes; ///< The sequence of nodes in the path.
};

/**
 * @brief The main graphical user interface for the Network Simulator.
 * * Manages the Qt graphics scene, user interactions, and coordinates
 * with the underlying logical core (SimulationManager, Commands, etc.).
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_btnAddServer_clicked();
    void on_btnAddRouter_clicked();
    void on_btnSaveNetwork_clicked();
    void on_btnLoadNetwork_clicked();
    void on_btnPingNetwork_clicked();
    void handleGuideClick();
    void on_btnCloneNetwork_clicked();

    void handleNodeConnection(VisualNode* source, VisualNode* target);
    void handleEdgeDeletion(VisualEdge* edge);
    void handleNodeDeletion(VisualNode* node);
    void handleNodeRename(VisualNode* node);
    void handleNodeStateToggle(VisualNode* node);
    void handleNodeFirewallToggle(VisualNode* node);
    void handleNodeStrategyChange(VisualNode* node, int type);
    void handlePathDeletion(int pathId, QWidget* widget);

private:
    void buildLogicalNetwork();
    void updateNetworkColors();
    void setupActivePathsPanel();
    void recalculateHighlights();
    void highlightPath(const std::vector<std::shared_ptr<NetworkNode>>& path);

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int serverCounter;
    int routerCounter;

    NetworkBuilder builder;
    std::shared_ptr<Subnet> activeNetwork;
    std::map<VisualNode*, std::shared_ptr<ServerNode>> coreNodes;

    QVBoxLayout* pathsLayout;
    int pathCounter;
    std::map<int, ActivePath> activePaths;
    QString generateCloneName(const QString& originalName);

    QLabel* lblDashboard;
    std::shared_ptr<DashboardObserver> dashboard;
};

#endif
