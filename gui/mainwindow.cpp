#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SimulationManager.h"
#include "MetricsCollector.h"
#include <QRandomGenerator>
#include <QFileDialog>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

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

    SimulationManager::getInstance().attach(std::make_shared<MetricsCollector>());

    builder.reset("Kyiv Core Network");
    activeNetwork = builder.getResult();

    ui->textEditLog->append("Visual UI Engine initialized.");
}

MainWindow::~MainWindow()
{
    delete ui;
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

    std::shared_ptr<ServerNode> logicalServer = std::make_shared<ServerNode>(serverName.toStdString());
    activeNetwork->addNode(logicalServer);
    nodeMapping[node] = logicalServer;

    ui->textEditLog->append("Added logical and visual " + serverName + " at X:" + QString::number(x) + " Y:" + QString::number(y));
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

    std::shared_ptr<ServerNode> logicalRouter = std::make_shared<ServerNode>(routerName.toStdString());
    activeNetwork->addNode(logicalRouter);
    nodeMapping[node] = logicalRouter;

    ui->textEditLog->append("Added logical and visual " + routerName + " at X:" + QString::number(x) + " Y:" + QString::number(y));
}

void MainWindow::handleNodeConnection(VisualNode* source, VisualNode* target) {
    VisualEdge* edge = new VisualEdge(source, target);
    scene->addItem(edge);
    connect(edge, &VisualEdge::edgeDeleted, this, &MainWindow::handleEdgeDeletion);

    auto sNode = nodeMapping[source];
    auto tNode = nodeMapping[target];
    if (sNode && tNode) {
        sNode->connectTo(tNode);
        tNode->connectTo(sNode);
    }

    ui->textEditLog->append("Connected " + source->getName() + " to " + target->getName());
}

void MainWindow::handleEdgeDeletion(VisualEdge* edge) {
    auto sNode = nodeMapping[edge->getSourceNode()];
    auto tNode = nodeMapping[edge->getTargetNode()];
    if (sNode && tNode) {
        sNode->removeConnection(tNode);
        tNode->removeConnection(sNode);
    }

    ui->textEditLog->append("Connection removed.");
    scene->removeItem(edge);
    delete edge;
}

void MainWindow::on_btnPingNetwork_clicked()
{
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
    if (!file.open(QIODevice::ReadOnly)) {
        ui->textEditLog->append("Error opening file for reading!");
        return;
    }

    QByteArray fileData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(fileData);
    if (doc.isNull() || !doc.isObject()) {
        ui->textEditLog->append("Invalid JSON format!");
        return;
    }

    scene->clear();
    nodeMapping.clear();
    serverCounter = 0;
    routerCounter = 0;

    builder.reset("Kyiv Loaded Network");
    activeNetwork = builder.getResult();

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
            node->setBrush(Qt::cyan);
            QString numStr = name;
            numStr.replace("Router-", "");
            int num = numStr.toInt();
            if (num > routerCounter) {
                routerCounter = num;
            }
        } else {
            QString numStr = name;
            numStr.replace("Server-", "");
            int num = numStr.toInt();
            if (num > serverCounter) {
                serverCounter = num;
            }
        }

        scene->addItem(node);

        connect(node, &VisualNode::connectionRequested, this, &MainWindow::handleNodeConnection);

        std::shared_ptr<ServerNode> logicalServer = std::make_shared<ServerNode>(name.toStdString());
        activeNetwork->addNode(logicalServer);
        nodeMapping[node] = logicalServer;
        createdNodes[name] = node;
    }

    for (const QJsonValue& val : edgesArray) {
        QJsonObject edgeObj = val.toObject();
        QString sourceName = edgeObj["source"].toString();
        QString targetName = edgeObj["target"].toString();

        if (createdNodes.count(sourceName) && createdNodes.count(targetName)) {
            handleNodeConnection(createdNodes[sourceName], createdNodes[targetName]);
        }
    }

    ui->textEditLog->append("Network successfully loaded from " + fileName);
}
