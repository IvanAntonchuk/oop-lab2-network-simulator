#include <gtest/gtest.h>
#include "ServerNode.h"
#include "SimulationManager.h"
#include "SimulationObserver.h"
#include "ReportFacade.h"
#include "NetworkBuilder.h"
#include "OnlineState.h"
#include "OfflineState.h"
#include <memory>
#include <string>
#include <algorithm>

TEST(NetworkLogicTest, ServerNodeManagesConnectionsCorrectly) {
    auto nodeA = std::make_shared<ServerNode>("A");
    auto nodeB = std::make_shared<ServerNode>("B");
    auto nodeC = std::make_shared<ServerNode>("C");

    nodeA->connectTo(nodeB);
    nodeA->connectTo(nodeC);

    EXPECT_EQ(nodeA->getConnections().size(), 2) << "Node A should have 2 connections.";

    auto connsA = nodeA->getConnections();
    bool isAConnectedToB = std::find(connsA.begin(), connsA.end(), nodeB) != connsA.end();
    EXPECT_TRUE(isAConnectedToB) << "Node A should be connected to B.";

    auto connsB = nodeB->getConnections();
    bool isBConnectedToC = std::find(connsB.begin(), connsB.end(), nodeC) != connsB.end();
    EXPECT_FALSE(isBConnectedToC) << "Node B should NOT be connected to C.";
}

class SpyObserver : public SimulationObserver {
public:
    bool wasNotified = false;
    std::string lastEvent = "";

    std::string update(const std::string& event) override {
        wasNotified = true;
        lastEvent = event;
        return "SpyNotified";
    }
};

TEST(CoreLogicTest, SimulationManagerNotifiesObservers) {
    auto& manager = SimulationManager::getInstance();
    auto spy = std::make_shared<SpyObserver>();

    manager.attach(spy);

    manager.notifyObservers("TEST_EVENT");

    EXPECT_TRUE(spy->wasNotified) << "Observer was not notified by SimulationManager.";
    EXPECT_EQ(spy->lastEvent, "TEST_EVENT") << "Observer received incorrect event data.";
}

TEST(CoreLogicTest, ReportFacadeGeneratesNonEmptyString) {
    auto network = std::make_shared<Subnet>("TestNet");
    network->addNode(std::make_shared<ServerNode>("Server1"));

    ReportFacade facade(network);
    std::string report = facade.generateNetworkReport();

    EXPECT_FALSE(report.empty()) << "ReportFacade generated an empty report.";
    EXPECT_TRUE(report.find("TestNet") != std::string::npos) << "Report does not contain network name.";
}

TEST(NetworkLogicTest, NodeTrafficDependsOnState) {
    auto server = std::make_shared<ServerNode>("TrafficServer");

    server->changeState(std::make_shared<OnlineState>());
    std::string onlineOutput = server->processTraffic();

    server->changeState(std::make_shared<OfflineState>());
    std::string offlineOutput = server->processTraffic();

    EXPECT_NE(onlineOutput, offlineOutput) << "Traffic output should change when node goes offline.";
}

TEST(CoreLogicTest, BuilderResetClearsPreviousBuild) {
    NetworkBuilder builder;
    builder.reset("Net-1");
    builder.addServer("S1");

    builder.reset("Net-2");
    auto result = builder.getResult();

    EXPECT_EQ(result->getName(), "Net-2") << "Builder did not reset the network name.";
    EXPECT_EQ(result->getNodes().size(), 0) << "Builder did not clear previous nodes on reset.";
}
