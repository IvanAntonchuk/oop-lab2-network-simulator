#ifndef ROUTINGSTRATEGY_H
#define ROUTINGSTRATEGY_H

#include <vector>
#include <memory>
#include <string>

class NetworkNode;

/**
 * @brief Interface for interchangeable packet routing algorithms (Strategy pattern).
 * * Allows dynamic switching between different pathfinding algorithms.
 */
class RoutingStrategy {
public:
    virtual ~RoutingStrategy() = default;

    /** @brief Calculates a path from the start node to the end node. */
    virtual std::vector<std::shared_ptr<NetworkNode>> calculatePath(
        std::shared_ptr<NetworkNode> start,
        std::shared_ptr<NetworkNode> end) = 0;

    /** @brief Gets the human-readable name of the strategy algorithm. */
    virtual std::string getName() const = 0;
};

#endif
