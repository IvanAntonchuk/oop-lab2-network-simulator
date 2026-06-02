#include "StarTopology.h"

StarTopology::StarTopology(std::shared_ptr<Subnet> subnet) : baseSubnet(subnet) {}

std::shared_ptr<TopologyPrototype> StarTopology::cloneTopology() const {
    auto clonedSubnet = std::static_pointer_cast<Subnet>(baseSubnet->clone());
    return std::make_shared<StarTopology>(clonedSubnet);
}

std::shared_ptr<Subnet> StarTopology::getNetwork() const {
    return baseSubnet;
}
