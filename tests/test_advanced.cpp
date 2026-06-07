#include <gtest/gtest.h>
#include "ServerNode.h"
#include "Subnet.h"
#include "SubnetIterator.h"
#include "OfflineState.h"
#include "ShortestPathStrategy.h"
#include <memory>
#include <string>

TEST(AdvancedPatternsTest, PrototypeCreatesIsolatedClones) {
    auto original = std::make_shared<ServerNode>("Proto-1");
    auto clone = std::dynamic_pointer_cast<ServerNode>(original->clone());

    ASSERT_NE(clone, nullptr) << "Prototype failed: Clone returned null.";
    EXPECT_NE(original.get(), clone.get()) << "Prototype failed: Clone has the same memory address as original.";

    EXPECT_NO_THROW(clone->changeState(std::make_shared<OfflineState>()))
        << "Prototype failed: Cannot mutate cloned object.";
}

TEST(AdvancedPatternsTest, IteratorTraversesSafely) {
    Subnet root("RootNet");
    root.addNode(std::make_shared<ServerNode>("Node1"));
    root.addNode(std::make_shared<ServerNode>("Node2"));

    auto sub = std::make_shared<Subnet>("ChildNet");
    sub->addNode(std::make_shared<ServerNode>("Node3"));
    root.addNode(sub);

    auto iterator = root.createIterator();
    int iterations = 0;

    while(iterator && iterator->hasNext()) {
        auto node = iterator->next();
        ASSERT_NE(node, nullptr);
        iterations++;
    }

    EXPECT_GT(iterations, 0) << "Iterator failed to traverse composite structure.";
}

TEST(CoreMechanicsTest, WeakPointersPreventMemoryLeaks) {
    auto stableNode = std::make_shared<ServerNode>("Stable");

    {
        auto temporaryNode = std::make_shared<ServerNode>("Temp");
        stableNode->connectTo(temporaryNode);
        temporaryNode->connectTo(stableNode);

    }

    EXPECT_NO_THROW(stableNode->processTraffic())
        << "Core failed: Traffic processing crashed! Weak pointers are not handling deleted neighbors correctly.";
}

TEST(CoreMechanicsTest, RoutingFailsSafelyWhenNetworkIsSplit) {
    auto nodeA = std::make_shared<ServerNode>("A");
    auto nodeB = std::make_shared<ServerNode>("B");

    ShortestPathStrategy strategy;
    auto path = strategy.calculatePath(nodeA, nodeB);

    EXPECT_TRUE(path.empty()) << "Routing failed: Expected empty path for strictly disconnected nodes.";
}

TEST(CoreMechanicsTest, SubnetHandlesMassiveScale) {
    Subnet massiveSubnet("Massive");

    for(int i = 0; i < 1000; i++) {
        massiveSubnet.addNode(std::make_shared<ServerNode>("Server_" + std::to_string(i)));
    }

    EXPECT_EQ(massiveSubnet.getNodes().size(), 1000) << "Core failed: Subnet could not store 1000 nodes.";

    EXPECT_NO_THROW(massiveSubnet.processTraffic())
        << "Core failed: Massive network crashed during traffic processing.";
}
