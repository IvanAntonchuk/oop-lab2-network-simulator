#ifndef NETWORKBUILDER_H
#define NETWORKBUILDER_H

#include "Subnet.h"
#include "ServerNode.h"
#include <memory>
#include <string>

/**
 * @brief Constructs complex network topologies step by step (Builder pattern).
 * * Provides methods to configure and build a Subnet, allowing the creation
 * of predefined structures like Star Topology easily.
 */
class NetworkBuilder {
private:
    std::shared_ptr<Subnet> currentSubnet;

public:
    NetworkBuilder();

    void reset(const std::string& subnetName);

    NetworkBuilder& addServer(const std::string& serverName);
    NetworkBuilder& addSubnet(std::shared_ptr<Subnet> subnet);
    NetworkBuilder& buildStarTopology(const std::string& routerName, int serverCount);

    std::shared_ptr<Subnet> getResult();
};

#endif
