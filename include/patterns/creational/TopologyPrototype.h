#ifndef TOPOLOGYPROTOTYPE_H
#define TOPOLOGYPROTOTYPE_H

#include "Subnet.h"
#include <memory>

class TopologyPrototype {
public:
    virtual ~TopologyPrototype() = default;
    virtual std::shared_ptr<TopologyPrototype> cloneTopology() const = 0;
    virtual std::shared_ptr<Subnet> getNetwork() const = 0;
};

#endif
