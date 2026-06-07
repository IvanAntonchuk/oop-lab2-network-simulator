#include <gtest/gtest.h>
#include "ServerNode.h"
#include "Subnet.h"
#include "ShortestPathStrategy.h"
#include "RandomPathStrategy.h"
#include "HistoryManager.h"
#include "OfflineState.h"
#include "ReportFacade.h"
#include "SimulationManager.h"
#include <memory>

TEST(EdgeCaseTest, RoutingHandlesCyclesWithoutInfiniteLoop) {
    auto nodeA = std::make_shared<ServerNode>("A");
    auto nodeB = std::make_shared<ServerNode>("B");
    auto nodeC = std::make_shared<ServerNode>("C");

    nodeA->connectTo(nodeB);
    nodeB->connectTo(nodeC);
    nodeC->connectTo(nodeA);

    ShortestPathStrategy strategy;
    auto path = strategy.calculatePath(nodeA, nodeC);

    EXPECT_FALSE(path.empty()) << "Routing failed to find path in a cyclic graph.";
}

TEST(EdgeCaseTest, RoutingIgnoresOfflineNodes) {
    auto nodeA = std::make_shared<ServerNode>("A");
    auto nodeB = std::make_shared<ServerNode>("B");
    auto nodeC = std::make_shared<ServerNode>("C");

    nodeA->connectTo(nodeB);
    nodeB->connectTo(nodeC);

    nodeB->changeState(std::make_shared<OfflineState>());

    ShortestPathStrategy strategy;
    auto path = strategy.calculatePath(nodeA, nodeC);

    EXPECT_TRUE(path.empty()) << "Routing should return empty path if the only route is offline.";
}

TEST(EdgeCaseTest, EmptyHistoryDoesNotCrash) {
    HistoryManager history(&SimulationManager::getInstance());

    EXPECT_NO_THROW(history.undo()) << "HistoryManager crashed on empty undo.";
    EXPECT_NO_THROW(history.redo()) << "HistoryManager crashed on empty redo.";
}

TEST(EdgeCaseTest, SubnetHandlesEmptyStateGracefully) {
    Subnet emptySubnet("Empty-Kyiv-Net");

    EXPECT_NO_THROW(emptySubnet.processTraffic()) << "Empty subnet crashed during traffic processing.";
    EXPECT_EQ(emptySubnet.getNodes().size(), 0);
}

TEST(EdgeCaseTest, ServerNodeIgnoresNonExistentConnectionsOnRemoval) {
    auto nodeA = std::make_shared<ServerNode>("A");
    auto nodeB = std::make_shared<ServerNode>("B");

    EXPECT_NO_THROW(nodeA->removeConnection(nodeB)) << "Node crashed when trying to remove a non-existent connection.";
}

TEST(EdgeCaseTest, RandomPathStrategyExecutesSafely) {
    auto nodeA = std::make_shared<ServerNode>("A");
    auto nodeB = std::make_shared<ServerNode>("B");
    nodeA->connectTo(nodeB);

    RandomPathStrategy strategy;
    EXPECT_NO_THROW({
        auto path = strategy.calculatePath(nodeA, nodeB);
    }) << "RandomPathStrategy crashed during execution.";
}

TEST(EdgeCaseTest, ReportFacadeHandlesEmptyNetwork) {
    auto emptyNet = std::make_shared<Subnet>("GhostNet");
    ReportFacade facade(emptyNet);

    std::string report;
    EXPECT_NO_THROW(report = facade.generateNetworkReport()) << "Facade crashed on empty network.";
    EXPECT_TRUE(report.find("GhostNet") != std::string::npos) << "Facade report missing network name.";
}
