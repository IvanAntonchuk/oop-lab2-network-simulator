#ifndef FIREWALLDECORATOR_H
#define FIREWALLDECORATOR_H

#include "NodeDecorator.h"

/**
 * @brief Concrete decorator that adds firewall protection to a node.
 * * Intercepts traffic before it reaches the wrapped node, simulating
 * packet filtering and security checks.
 */
class FirewallDecorator : public NodeDecorator {
private:
    std::string blockMaliciousPackets();

public:
    explicit FirewallDecorator(std::shared_ptr<NetworkNode> node);

    std::string processTraffic() override;
    std::shared_ptr<NetworkNode> clone() const override;
};

#endif
