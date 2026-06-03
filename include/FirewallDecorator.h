#ifndef FIREWALLDECORATOR_H
#define FIREWALLDECORATOR_H

#include "NodeDecorator.h"

class FirewallDecorator : public NodeDecorator {
private:
    std::string blockMaliciousPackets();

public:
    explicit FirewallDecorator(std::shared_ptr<NetworkNode> node);

    std::string processTraffic() override;
    std::shared_ptr<NetworkNode> clone() const override;
};

#endif
