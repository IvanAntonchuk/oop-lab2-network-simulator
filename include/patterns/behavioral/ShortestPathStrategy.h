#ifndef SHORTESTPATHSTRATEGY_H
#define SHORTESTPATHSTRATEGY_H

#include "RoutingStrategy.h"
#include <vector>
#include <memory>
#include <string>

class ShortestPathStrategy : public RoutingStrategy {
public:
    std::vector<std::shared_ptr<NetworkNode>> calculatePath(
        std::shared_ptr<NetworkNode> source,
        std::shared_ptr<NetworkNode> destination) override;

    std::string getName() const override;
};

#endif
