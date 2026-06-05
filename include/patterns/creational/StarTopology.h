#ifndef STARTOPOLOGY_H
#define STARTOPOLOGY_H

#include "TopologyPrototype.h"
#include "Subnet.h"

class StarTopology : public TopologyPrototype {
private:
    std::shared_ptr<Subnet> baseSubnet;
public:
    explicit StarTopology(std::shared_ptr<Subnet> subnet);
    std::shared_ptr<TopologyPrototype> cloneTopology() const override;
    std::shared_ptr<Subnet> getNetwork() const override;
};

#endif
