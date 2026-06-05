#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SimulationManager.h"
#include "MetricsCollector.h"
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    ui->graphicsView->setScene(scene);
    scene->setSceneRect(0, 0, 1000, 600);

    SimulationManager::getInstance().attach(std::make_shared<MetricsCollector>());

    ui->textEditLog->append("Visual UI Engine initialized.");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnAddServer_clicked()
{
    int x = QRandomGenerator::global()->bounded(100, 800);
    int y = QRandomGenerator::global()->bounded(50, 500);

    QGraphicsEllipseItem* node = new QGraphicsEllipseItem(0, 0, 50, 50);
    node->setPos(x, y);
    node->setBrush(Qt::green);
    node->setFlag(QGraphicsItem::ItemIsMovable);

    QGraphicsTextItem* text = new QGraphicsTextItem("Server", node);
    text->setPos(3, 13);

    scene->addItem(node);

    ui->textEditLog->append("Visual node added to canvas at X:" + QString::number(x) + " Y:" + QString::number(y));
}

void MainWindow::on_btnSaveNetwork_clicked()
{
    ui->textEditLog->append("Initiating JSON serialization module...");
}

void MainWindow::on_btnLoadNetwork_clicked()
{
    ui->textEditLog->append("Initiating JSON deserialization module...");
}
