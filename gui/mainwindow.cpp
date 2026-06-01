#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Subnet.h"
#include "ServerNode.h"
#include "ShortestPathStrategy.h"
#include "RandomPathStrategy.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnTestComposite_clicked()
{
    std::shared_ptr<Subnet> globalNetwork = std::make_shared<Subnet>("Global Internet");

    std::shared_ptr<Subnet> kievSubnet = std::make_shared<Subnet>("Kyiv Datacenter");
    kievSubnet->addNode(std::make_shared<ServerNode>("Server-K1"));
    kievSubnet->addNode(std::make_shared<ServerNode>("Server-K2"));

    std::shared_ptr<ServerNode> standaloneServer = std::make_shared<ServerNode>("Standalone-S1");

    globalNetwork->addNode(kievSubnet);
    globalNetwork->addNode(standaloneServer);

    std::string result = globalNetwork->processTraffic();

    ui->textEditLog->append(QString::fromStdString(result));
    ui->textEditLog->append("--------------------------------------------------\n");
}

void MainWindow::on_btnTestStrategy_clicked()
{
    ui->textEditLog->append("--- Тестування патерну Strategy ---");

    std::shared_ptr<ServerNode> myServer = std::make_shared<ServerNode>("Main-Router");

    myServer->setStrategy(std::make_shared<ShortestPathStrategy>());
    ui->textEditLog->append(QString::fromStdString(myServer->processTraffic()));

    myServer->setStrategy(std::make_shared<RandomPathStrategy>());
    ui->textEditLog->append(QString::fromStdString(myServer->processTraffic()));

    myServer->setStrategy(nullptr);
    ui->textEditLog->append(QString::fromStdString(myServer->processTraffic()));

    ui->textEditLog->append("--------------------------------------------------\n");
}
