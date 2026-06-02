#include "NetworkBuilder.h"

NetworkBuilder::NetworkBuilder() {
    reset("Default Subnet");
}

void NetworkBuilder::reset(const std::string& subnetName) {
    currentSubnet = std::make_shared<Subnet>(subnetName);
}

NetworkBuilder& NetworkBuilder::addServer(const std::string& serverName) {
    if (currentSubnet) {
        currentSubnet->addNode(std::make_shared<ServerNode>(serverName));
    }
    return *this;
}

NetworkBuilder& NetworkBuilder::addSubnet(std::shared_ptr<Subnet> subnet) {
    if (currentSubnet && subnet) {
        currentSubnet->addNode(subnet);
    }
    return *this;
}

std::shared_ptr<Subnet> NetworkBuilder::getResult() {
    std::shared_ptr<Subnet> result = currentSubnet;
    reset("New Subnet");
    return result;
}
