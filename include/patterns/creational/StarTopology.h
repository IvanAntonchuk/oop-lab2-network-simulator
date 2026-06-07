#ifndef STARTOPOLOGY_H
#define STARTOPOLOGY_H

#include "TopologyPrototype.h"
#include "Subnet.h"

/**
 * @brief Represents a pre-configured Star Topology network.
 * * Implements the Prototype pattern to allow quick cloning of a
 * standard star network configuration.
 */
class StarTopology : public TopologyPrototype {
private:
    std::shared_ptr<Subnet> baseSubnet;
public:
    explicit StarTopology(std::shared_ptr<Subnet> subnet);
    std::shared_ptr<TopologyPrototype> cloneTopology() const override;
    std::shared_ptr<Subnet> getNetwork() const override;
};

#endif
