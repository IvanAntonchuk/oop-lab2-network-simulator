#include "FirewallDecorator.h"

FirewallDecorator::FirewallDecorator(std::shared_ptr<NetworkNode> node)
    : NodeDecorator(node) {}

std::string FirewallDecorator::blockMaliciousPackets() {
    return "[Firewall] Blocking malicious packets... ";
}

std::string FirewallDecorator::processTraffic() {
    std::string log = blockMaliciousPackets();
    log += NodeDecorator::processTraffic();
    return log;
}

std::shared_ptr<NetworkNode> FirewallDecorator::clone() const {
    auto clonedWrappee = wrappee ? wrappee->clone() : nullptr;
    return std::make_shared<FirewallDecorator>(clonedWrappee);
}
