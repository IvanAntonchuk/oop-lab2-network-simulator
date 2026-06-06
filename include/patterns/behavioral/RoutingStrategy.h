#ifndef ROUTINGSTRATEGY_H
#define ROUTINGSTRATEGY_H

#include <vector>
#include <memory>
#include <string>

class NetworkNode;

class RoutingStrategy {
public:
    virtual ~RoutingStrategy() = default;

    virtual std::vector<std::shared_ptr<NetworkNode>> calculatePath(
        std::shared_ptr<NetworkNode> start,
        std::shared_ptr<NetworkNode> end) = 0;

    virtual std::string getName() const = 0;
};

#endif
