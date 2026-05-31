#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Subnet.h"
#include "ServerNode.h"
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
