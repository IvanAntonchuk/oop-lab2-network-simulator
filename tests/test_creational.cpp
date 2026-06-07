#include <gtest/gtest.h>
#include "SimulationManager.h"
#include "NetworkBuilder.h"
#include "ServerNode.h"
#include "Subnet.h"

// ТЕСТИ ПОРОДЖУВАЛЬНИХ ПАТЕРНІВ (CREATIONAL)

TEST(CreationalPatternsTest, SingletonInstanceIsUnique) {
    SimulationManager& instance1 = SimulationManager::getInstance();
    SimulationManager& instance2 = SimulationManager::getInstance();

    EXPECT_EQ(&instance1, &instance2) << "Singleton failed: Instances are not the same object in memory.";
}

TEST(CreationalPatternsTest, BuilderCreatesStarTopologyCorrectly) {
    NetworkBuilder builder;
    builder.reset("Kyiv Star Network");

    builder.buildStarTopology("Core-Router", 4);
    auto network = builder.getResult();

    ASSERT_NE(network, nullptr) << "Builder failed: Resulting network is null.";
    EXPECT_EQ(network->getName(), "Kyiv Star Network");

    auto nodes = network->getNodes();
    EXPECT_EQ(nodes.size(), 5) << "Builder failed: Incorrect number of total nodes.";

    bool routerFound = false;
    for (const auto& node : nodes) {
        if (node->getName() == "Core-Router") {
            routerFound = true;
            EXPECT_EQ(node->getConnections().size(), 4) << "Builder failed: Central router is not connected to all leaf servers.";
        }
    }
    EXPECT_TRUE(routerFound) << "Builder failed: Central router was not created.";
}
