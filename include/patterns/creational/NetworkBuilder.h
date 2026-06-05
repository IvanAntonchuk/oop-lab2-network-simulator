#ifndef NETWORKBUILDER_H
#define NETWORKBUILDER_H

#include "Subnet.h"
#include "ServerNode.h"
#include <memory>
#include <string>

class NetworkBuilder {
private:
    std::shared_ptr<Subnet> currentSubnet;

public:
    NetworkBuilder();

    void reset(const std::string& subnetName);

    NetworkBuilder& addServer(const std::string& serverName);
    NetworkBuilder& addSubnet(std::shared_ptr<Subnet> subnet);

    std::shared_ptr<Subnet> getResult();
};

#endif // NETWORKBUILDER_H
