#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SimulationManager.h"
#include "MetricsCollector.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
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

    QGraphicsEllipseItem* node = new QGraphicsEllipseItem(0, 0, 70, 70);
    node->setPos(x, y);
    node->setBrush(Qt::green);
    node->setFlag(QGraphicsItem::ItemIsMovable);

    QString serverName = "Server-" + QString::number(serverCounter);
    QGraphicsTextItem* text = new QGraphicsTextItem(serverName, node);
    text->setDefaultTextColor(Qt::black);
    text->setPos(10, 23);

    scene->addItem(node);

    std::shared_ptr<ServerNode> logicalServer = std::make_shared<ServerNode>(serverName.toStdString());
    activeNetwork->addNode(logicalServer);
    nodeMapping[node] = logicalServer;

    ui->textEditLog->append("Added logical and visual " + serverName + " at X:" + QString::number(x) + " Y:" + QString::number(y));
}

void MainWindow::on_btnSaveNetwork_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save Network", "kyiv_network.json", "JSON Files (*.json)");
    if (fileName.isEmpty()) return;

    QJsonArray nodesArray;

    for (QGraphicsItem* item : scene->items()) {
        if (item->parentItem() == nullptr) {
            QGraphicsEllipseItem* ellipse = dynamic_cast<QGraphicsEllipseItem*>(item);
            if (ellipse) {
                QJsonObject nodeObj;
                nodeObj["x"] = ellipse->pos().x();
                nodeObj["y"] = ellipse->pos().y();

                for (QGraphicsItem* child : ellipse->childItems()) {
                    QGraphicsTextItem* textItem = dynamic_cast<QGraphicsTextItem*>(child);
                    if (textItem) {
                        nodeObj["name"] = textItem->toPlainText();
                        break;
                    }
                }
                nodesArray.append(nodeObj);
            }
        }
    }

    QJsonObject networkObj;
    networkObj["nodes"] = nodesArray;

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

    builder.reset("Kyiv Loaded Network");
    activeNetwork = builder.getResult();

    QJsonObject networkObj = doc.object();
    QJsonArray nodesArray = networkObj["nodes"].toArray();

    for (const QJsonValue& val : nodesArray) {
        QJsonObject nodeObj = val.toObject();
        double x = nodeObj["x"].toDouble();
        double y = nodeObj["y"].toDouble();
        QString name = nodeObj["name"].toString();

        QGraphicsEllipseItem* node = new QGraphicsEllipseItem(0, 0, 70, 70);
        node->setPos(x, y);
        node->setBrush(Qt::green);
        node->setFlag(QGraphicsItem::ItemIsMovable);

        QGraphicsTextItem* text = new QGraphicsTextItem(name, node);
        text->setDefaultTextColor(Qt::black);
        text->setPos(10, 23);

        scene->addItem(node);

        std::shared_ptr<ServerNode> logicalServer = std::make_shared<ServerNode>(name.toStdString());
        activeNetwork->addNode(logicalServer);
        nodeMapping[node] = logicalServer;

        QString numStr = name;
        numStr.replace("Server-", "");
        int num = numStr.toInt();
        if (num > serverCounter) {
            serverCounter = num;
        }
    }

    ui->textEditLog->append("Network successfully loaded from " + fileName);
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
