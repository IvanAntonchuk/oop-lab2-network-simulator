#include <gtest/gtest.h>
#include "Subnet.h"
#include "ServerNode.h"
#include "FirewallDecorator.h"
#include <memory>

// ТЕСТИ СТРУКТУРНИХ ПАТЕРНІВ (STRUCTURAL)

TEST(StructuralPatternsTest, CompositeSubnetHierarchy) {
    auto rootNetwork = std::make_shared<Subnet>("Root-Net");
    auto branchNetwork = std::make_shared<Subnet>("Branch-Net");
    auto server1 = std::make_shared<ServerNode>("Server-1");
    auto server2 = std::make_shared<ServerNode>("Server-2");

    branchNetwork->addNode(server1);

    rootNetwork->addNode(branchNetwork);
    rootNetwork->addNode(server2);

    EXPECT_EQ(rootNetwork->getNodes().size(), 2) << "Composite failed: Root network should contain 2 elements.";

    EXPECT_EQ(branchNetwork->getNodes().size(), 1) << "Composite failed: Branch subnet should contain 1 element.";

    EXPECT_EQ(branchNetwork->getName(), "Branch-Net") << "Composite failed: Incorrect node name.";
}

TEST(StructuralPatternsTest, FirewallDecoratorWrapsCorrectly) {
    auto baseServer = std::make_shared<ServerNode>("TargetServer");

    auto secureServer = std::make_shared<FirewallDecorator>(baseServer);

    EXPECT_NE(secureServer, nullptr) << "Decorator failed: Wrapped object is null.";

    EXPECT_NO_THROW(secureServer->processTraffic()) << "Decorator failed: processTraffic threw an exception.";
}
