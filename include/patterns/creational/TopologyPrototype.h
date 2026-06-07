#ifndef TOPOLOGYPROTOTYPE_H
#define TOPOLOGYPROTOTYPE_H

#include "Subnet.h"
#include <memory>

/**
 * @brief Interface for cloning network topologies (Prototype pattern).
 * * Allows creating deep copies of complex objects or entire network
 * structures without coupling code to their specific classes.
 */
class TopologyPrototype {
public:
    virtual ~TopologyPrototype() = default;
    virtual std::shared_ptr<TopologyPrototype> cloneTopology() const = 0;
    virtual std::shared_ptr<Subnet> getNetwork() const = 0;
};

#endif
