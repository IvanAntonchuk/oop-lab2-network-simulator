#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SimulationManager.h"
#include "MetricsCollector.h"
#include "OnlineState.h"
#include "OfflineState.h"
#include "FirewallDecorator.h"
#include <QRandomGenerator>
#include <QFileDialog>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QInputDialog>
#include <QSet>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , serverCounter(0)
    , routerCounter(0)
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 1000, 600);

    QPushButton* btnGuide = new QPushButton("Guide", this);
    ui->horizontalLayout->addWidget(btnGuide);
    connect(btnGuide, &QPushButton::clicked, this, &MainWindow::handleGuideClick);

    SimulationManager::getInstance().attach(std::make_shared<MetricsCollector>());
    ui->textEditLog->append("Visual UI Engine initialized.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleGuideClick() {
    QString guideText =
        "<h3>Network Simulator Guide</h3>"
        "<ul>"
        "<li><b>Router (Square):</b> Entry point for traffic.</li>"
        "<li><b>Server (Circle):</b> Processing node.</li>"
        "<li><b>Green:</b> Operational and connected.</li>"
        "<li><b>Yellow:</b> Operational but isolated (no connection).</li>"
        "<li><b>Red:</b> Offline (power down).</li>"
        "<li><b>Blue Border:</b> Firewall active.</li>"
        "</ul>";

    QMessageBox::information(this, "Network Guide", guideText);
}

void MainWindow::updateNetworkColors() {
    QList<VisualNode*> allNodes;
    for (QGraphicsItem* item : scene->items()) {
        VisualNode* vNode = dynamic_cast<VisualNode*>(item);
        if (vNode) {
            vNode->setReachable(false);
            allNodes.append(vNode);
        }
    }

    QList<VisualNode*> queue;
    QSet<VisualNode*> visited;

    for (VisualNode* vNode : allNodes) {
        if (vNode->getName().startsWith("Router") && !vNode->getIsOffline()) {
            queue.append(vNode);
            visited.insert(vNode);
            vNode->setReachable(true);
        }
    }

    while (!queue.isEmpty()) {
        VisualNode* current = queue.takeFirst();
        for (VisualEdge* edge : current->getEdges()) {
            VisualNode* neighbor = (edge->getSourceNode() == current) ? edge->getTargetNode() : edge->getSourceNode();
            if (!neighbor->getIsOffline() && !visited.contains(neighbor)) {
                visited.insert(neighbor);
                neighbor->setReachable(true);
                queue.append(neighbor);
            }
        }
    }
}

void MainWindow::on_btnAddServer_clicked()
{
    serverCounter++;
    int x = QRandomGenerator::global()->bounded(100, 800);
    int y = QRandomGenerator::global()->bounded(50, 500);
    QString serverName = "Server-" + QString::number(serverCounter);

    VisualNode* node = new VisualNode(serverName);
    node->setPos(x, y);
    scene->addItem(node);

    connect(node, &VisualNode::connectionRequested, this, &MainWindow::handleNodeConnection);
    connect(node, &VisualNode::nodeDeleted, this, &MainWindow::handleNodeDeletion);
    connect(node, &VisualNode::renameRequested, this, &MainWindow::handleNodeRename);
    connect(node, &VisualNode::toggleStateRequested, this, &MainWindow::handleNodeStateToggle);
    connect(node, &VisualNode::toggleFirewallRequested, this, &MainWindow::handleNodeFirewallToggle);

    coreNodes[node] = std::make_shared<ServerNode>(serverName.toStdString());
    ui->textEditLog->append("Added visual " + serverName + " at X:" + QString::number(x) + " Y:" + QString::number(y));
    updateNetworkColors();
}

void MainWindow::on_btnAddRouter_clicked()
{
    routerCounter++;
    int x = QRandomGenerator::global()->bounded(100, 800);
    int y = QRandomGenerator::global()->bounded(50, 500);
    QString routerName = "Router-" + QString::number(routerCounter);

    VisualNode* node = new VisualNode(routerName);
    node->setPos(x, y);
    node->setBrush(Qt::cyan);
    scene->addItem(node);

    connect(node, &VisualNode::connectionRequested, this, &MainWindow::handleNodeConnection);
    connect(node, &VisualNode::nodeDeleted, this, &MainWindow::handleNodeDeletion);
    connect(node, &VisualNode::renameRequested, this, &MainWindow::handleNodeRename);
    connect(node, &VisualNode::toggleStateRequested, this, &MainWindow::handleNodeStateToggle);
    connect(node, &VisualNode::toggleFirewallRequested, this, &MainWindow::handleNodeFirewallToggle);

    coreNodes[node] = std::make_shared<ServerNode>(routerName.toStdString());
    ui->textEditLog->append("Added visual " + routerName + " at X:" + QString::number(x) + " Y:" + QString::number(y));
    updateNetworkColors();
}

void MainWindow::handleNodeConnection(VisualNode* source, VisualNode* target) {
    VisualEdge* edge = new VisualEdge(source, target);
    scene->addItem(edge);
    connect(edge, &VisualEdge::edgeDeleted, this, &MainWindow::handleEdgeDeletion);
    ui->textEditLog->append("Connected " + source->getName() + " to " + target->getName());
    updateNetworkColors();
}

void MainWindow::handleEdgeDeletion(VisualEdge* edge) {
    ui->textEditLog->append("Connection removed.");
    scene->removeItem(edge);
    delete edge;
    updateNetworkColors();
}

void MainWindow::buildLogicalNetwork() {
    builder.reset("Kyiv Core Network");
    activeNetwork = builder.getResult();

    std::map<QString, std::shared_ptr<NetworkNode>> pingMapping;

    for (auto const& [vNode, sNode] : coreNodes) {
        sNode->clearConnections();
        std::shared_ptr<NetworkNode> finalNode = sNode;
        if (vNode->getHasFirewall()) {
            finalNode = std::make_shared<FirewallDecorator>(sNode);
        }
        activeNetwork->addNode(finalNode);
        pingMapping[vNode->getName()] = finalNode;
    }

    for (QGraphicsItem* item : scene->items()) {
        VisualEdge* vEdge = dynamic_cast<VisualEdge*>(item);
        if (vEdge) {
            auto sNode = pingMapping[vEdge->getSourceNode()->getName()];
            auto tNode = pingMapping[vEdge->getTargetNode()->getName()];
            if (sNode && tNode) {
                sNode->connectTo(tNode);
                tNode->connectTo(sNode);
            }
        }
    }
}

void MainWindow::on_btnPingNetwork_clicked()
{
    buildLogicalNetwork();
    ui->textEditLog->append("--- Pinging Logical Network ---");
    if (activeNetwork) {
        std::string log = activeNetwork->processTraffic();
        ui->textEditLog->append(QString::fromStdString(log));
    }
    ui->textEditLog->append("-------------------------------");
}

void MainWindow::on_btnSaveNetwork_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Network", "kyiv_network.json", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QJsonArray nodesArray;
    QJsonArray edgesArray;

    for (QGraphicsItem* item : scene->items()) {
        VisualNode* vNode = dynamic_cast<VisualNode*>(item);
        if (vNode) {
            QJsonObject nodeObj;
            nodeObj["x"] = vNode->pos().x();
            nodeObj["y"] = vNode->pos().y();
            nodeObj["name"] = vNode->getName();
            nodeObj["offline"] = vNode->getIsOffline();
            nodeObj["firewall"] = vNode->getHasFirewall();
            nodesArray.append(nodeObj);
        }
        VisualEdge* vEdge = dynamic_cast<VisualEdge*>(item);
        if (vEdge) {
            QJsonObject edgeObj;
            edgeObj["source"] = vEdge->getSourceNode()->getName();
            edgeObj["target"] = vEdge->getTargetNode()->getName();
            edgesArray.append(edgeObj);
        }
    }

    QJsonObject networkObj;
    networkObj["nodes"] = nodesArray;
    networkObj["edges"] = edgesArray;

    QJsonDocument doc(networkObj);
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(doc.toJson());
        file.close();
        ui->textEditLog->append("Network successfully saved to " + fileName);
    } else {
        ui->textEditLog->append("Error saving file!");
    }
}

void MainWindow::on_btnLoadNetwork_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Load Network", "", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    if (doc.isNull() || !doc.isObject()) return;

    scene->clear();
    coreNodes.clear();
    serverCounter = 0;
    routerCounter = 0;

    QJsonObject networkObj = doc.object();
    QJsonArray nodesArray = networkObj["nodes"].toArray();
    QJsonArray edgesArray = networkObj["edges"].toArray();

    std::map<QString, VisualNode*> createdNodes;

    for (const QJsonValue& val : nodesArray) {
        QJsonObject nodeObj = val.toObject();
        double x = nodeObj["x"].toDouble();
        double y = nodeObj["y"].toDouble();
        QString name = nodeObj["name"].toString();

        VisualNode* node = new VisualNode(name);
        node->setPos(x, y);

        if (name.startsWith("Router")) {
            QString numStr = name; numStr.replace("Router-", "");
            if (numStr.toInt() > routerCounter) routerCounter = numStr.toInt();
        } else {
            QString numStr = name; numStr.replace("Server-", "");
            if (numStr.toInt() > serverCounter) serverCounter = numStr.toInt();
        }

        scene->addItem(node);
        node->setOffline(nodeObj["offline"].toBool());
        node->setFirewall(nodeObj["firewall"].toBool());

        connect(node, &VisualNode::connectionRequested, this, &MainWindow::handleNodeConnection);
        connect(node, &VisualNode::nodeDeleted, this, &MainWindow::handleNodeDeletion);
        connect(node, &VisualNode::renameRequested, this, &MainWindow::handleNodeRename);
        connect(node, &VisualNode::toggleStateRequested, this, &MainWindow::handleNodeStateToggle);
        connect(node, &VisualNode::toggleFirewallRequested, this, &MainWindow::handleNodeFirewallToggle);

        coreNodes[node] = std::make_shared<ServerNode>(name.toStdString());
        createdNodes[name] = node;
    }

    for (const QJsonValue& val : edgesArray) {
        QJsonObject edgeObj = val.toObject();
        QString sourceName = edgeObj["source"].toString();
        QString targetName = edgeObj["target"].toString();

        if (createdNodes.count(sourceName) && createdNodes.count(targetName)) {
            VisualEdge* edge = new VisualEdge(createdNodes[sourceName], createdNodes[targetName]);
            scene->addItem(edge);
            connect(edge, &VisualEdge::edgeDeleted, this, &MainWindow::handleEdgeDeletion);
        }
    }
    ui->textEditLog->append("Network successfully loaded from " + fileName);
    updateNetworkColors();
}

void MainWindow::handleNodeDeletion(VisualNode* node) {
    QList<VisualEdge*> connectedEdges = node->getEdges();
    for (VisualEdge* edge : connectedEdges) {
        handleEdgeDeletion(edge);
    }
    coreNodes.erase(node);
    scene->removeItem(node);
    delete node;
    ui->textEditLog->append("Node deleted.");
    updateNetworkColors();
}

void MainWindow::handleNodeRename(VisualNode* node) {
    bool ok;
    QString newName = QInputDialog::getText(this, "Rename Node", "New name:", QLineEdit::Normal, node->getName(), &ok);
    if (ok && !newName.isEmpty() && newName != node->getName()) {
        QString oldName = node->getName();
        node->setName(newName);
        if (coreNodes[node]) coreNodes[node]->setName(newName.toStdString());
        ui->textEditLog->append("Renamed " + oldName + " to " + newName);
    }
}

void MainWindow::handleNodeStateToggle(VisualNode* node) {
    auto sNode = coreNodes[node];
    if (sNode) {
        node->setOffline(!node->getIsOffline());
        if (node->getIsOffline()) {
            sNode->changeState(std::make_shared<OfflineState>());
            ui->textEditLog->append(node->getName() + " turned OFFLINE");
        } else {
            sNode->changeState(std::make_shared<OnlineState>());
            ui->textEditLog->append(node->getName() + " turned ONLINE");
        }
        updateNetworkColors();
    }
}

void MainWindow::handleNodeFirewallToggle(VisualNode* node) {
    node->setFirewall(!node->getHasFirewall());
    QString status = node->getHasFirewall() ? "added" : "removed";
    ui->textEditLog->append("Firewall " + status + " on " + node->getName());
}
