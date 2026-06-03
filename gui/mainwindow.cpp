#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Subnet.h"
#include "ServerNode.h"
#include "ShortestPathStrategy.h"
#include "RandomPathStrategy.h"
#include "StartCommand.h"
#include "PauseCommand.h"
#include "OnlineState.h"
#include "OfflineState.h"
#include "NetworkBuilder.h"
#include "StarTopology.h"
#include "FirewallDecorator.h"
#include "ReportFacade.h"
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

    std::shared_ptr<Subnet> kyivSubnet = std::make_shared<Subnet>("Kyiv Datacenter");
    kyivSubnet->addNode(std::make_shared<ServerNode>("Server-K1"));
    kyivSubnet->addNode(std::make_shared<ServerNode>("Server-K2"));

    std::shared_ptr<ServerNode> standaloneServer = std::make_shared<ServerNode>("Standalone-S1");

    globalNetwork->addNode(kyivSubnet);
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

void MainWindow::on_btnStartSimulation_clicked()
{
    std::unique_ptr<SimulationCommand> startCmd = std::make_unique<StartCommand>();
    std::string result = startCmd->execute();
    ui->textEditLog->append(QString::fromStdString(result));
}

void MainWindow::on_btnPauseSimulation_clicked()
{
    std::unique_ptr<SimulationCommand> pauseCmd = std::make_unique<PauseCommand>();
    std::string result = pauseCmd->execute();
    ui->textEditLog->append(QString::fromStdString(result));
}

void MainWindow::on_btnTestState_clicked()
{
    ui->textEditLog->append("--- Тестування патерну State ---");

    std::shared_ptr<ServerNode> dbServer = std::make_shared<ServerNode>("DB-Server");
    ui->textEditLog->append(QString::fromStdString(dbServer->processTraffic()));

    dbServer->changeState(std::make_shared<OfflineState>());
    ui->textEditLog->append(QString::fromStdString(dbServer->processTraffic()));

    dbServer->changeState(std::make_shared<OnlineState>());
    ui->textEditLog->append(QString::fromStdString(dbServer->processTraffic()));

    ui->textEditLog->append("--------------------------------------------------\n");
}

void MainWindow::on_btnTestBuilder_clicked()
{
    ui->textEditLog->append("--- Тестування патерну Builder ---");

    NetworkBuilder builder;

    builder.reset("Kyiv Datacenter");
    builder.addServer("Server-K1").addServer("Server-K2").addServer("Server-K3");
    std::shared_ptr<Subnet> kyivSubnet = builder.getResult();

    builder.reset("Global Internet");
    builder.addServer("Standalone-S1").addSubnet(kyivSubnet);
    std::shared_ptr<Subnet> globalNetwork = builder.getResult();

    ui->textEditLog->append(QString::fromStdString(globalNetwork->processTraffic()));
    ui->textEditLog->append("--------------------------------------------------\n");
}

void MainWindow::on_btnTestPrototype_clicked()
{
    ui->textEditLog->append("--- Тестування патерну Prototype ---");

    std::shared_ptr<Subnet> basePattern = std::make_shared<Subnet>("Star-Core-Router");
    basePattern->addNode(std::make_shared<ServerNode>("Node-A"));
    basePattern->addNode(std::make_shared<ServerNode>("Node-B"));

    StarTopology prototype(basePattern);

    std::shared_ptr<TopologyPrototype> clone1 = prototype.cloneTopology();
    std::shared_ptr<TopologyPrototype> clone2 = prototype.cloneTopology();

    ui->textEditLog->append("[ОРИГІНАЛ]:");
    ui->textEditLog->append(QString::fromStdString(prototype.getNetwork()->processTraffic()));

    ui->textEditLog->append("[КЛОН 1]:");
    ui->textEditLog->append(QString::fromStdString(clone1->getNetwork()->processTraffic()));

    ui->textEditLog->append("[КЛОН 2]:");
    ui->textEditLog->append(QString::fromStdString(clone2->getNetwork()->processTraffic()));

    ui->textEditLog->append("--------------------------------------------------\n");
}

void MainWindow::on_btnTestDecorator_clicked()
{
    ui->textEditLog->append("--- Testing Decorator pattern ---");

    std::shared_ptr<ServerNode> regularServer = std::make_shared<ServerNode>("Web-Server");
    ui->textEditLog->append("[Unprotected]:");
    ui->textEditLog->append(QString::fromStdString(regularServer->processTraffic()));

    std::shared_ptr<NetworkNode> secureServer = std::make_shared<FirewallDecorator>(regularServer);
    ui->textEditLog->append("[Protected by Firewall]:");
    ui->textEditLog->append(QString::fromStdString(secureServer->processTraffic()));

    ui->textEditLog->append("--------------------------------------------------\n");
}

void MainWindow::on_btnTestFacade_clicked()
{
    ui->textEditLog->append("--- Testing Facade pattern ---");

    NetworkBuilder builder;
    builder.reset("Kyiv Main Network");
    builder.addServer("Web-Server").addServer("DB-Server");
    std::shared_ptr<Subnet> myNetwork = builder.getResult();

    ReportFacade facade(myNetwork);
    std::string report = facade.generateNetworkReport();

    ui->textEditLog->append(QString::fromStdString(report));
    ui->textEditLog->append("--------------------------------------------------\n");
}
