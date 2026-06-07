#ifndef RANDOMPATHSTRATEGY_H
#define RANDOMPATHSTRATEGY_H

#include "RoutingStrategy.h"
#include <vector>
#include <memory>
#include <string>
#include <set>

/**
 * @brief Concrete strategy implementing Randomized DFS routing (Strategy pattern).
 * * Explores paths randomly using Depth-First Search with backtracking.
 */
class RandomPathStrategy : public RoutingStrategy {
private:
    bool dfs(std::shared_ptr<NetworkNode> current,
             std::shared_ptr<NetworkNode> target,
             std::set<std::string>& visited,
             std::vector<std::shared_ptr<NetworkNode>>& path) const;

public:
    std::vector<std::shared_ptr<NetworkNode>> calculatePath(
        std::shared_ptr<NetworkNode> source,
        std::shared_ptr<NetworkNode> destination) override;

    std::string getName() const override;
};

#endif
