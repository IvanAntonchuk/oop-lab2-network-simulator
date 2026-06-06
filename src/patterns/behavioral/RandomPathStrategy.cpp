#include "RandomPathStrategy.h"
#include "NetworkNode.h"
#include <algorithm>
#include <random>
#include <chrono>

std::string RandomPathStrategy::getName() const {
    return "Randomized DFS with Backtracking";
}

std::vector<std::shared_ptr<NetworkNode>> RandomPathStrategy::calculatePath(
    std::shared_ptr<NetworkNode> source,
    std::shared_ptr<NetworkNode> destination) {

    std::vector<std::shared_ptr<NetworkNode>> path;
    std::set<std::string> visited;

    if (!source || !destination) return path;

    if (dfs(source, destination, visited, path)) {
        return path;
    }

    return {};
}

bool RandomPathStrategy::dfs(std::shared_ptr<NetworkNode> current,
                             std::shared_ptr<NetworkNode> target,
                             std::set<std::string>& visited,
                             std::vector<std::shared_ptr<NetworkNode>>& path) const {
    visited.insert(current->getName());
    path.push_back(current);

    if (current->getName() == target->getName()) {
        return true;
    }

    auto neighbors = current->getConnections();

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);

    std::shuffle(neighbors.begin(), neighbors.end(), generator);

    for (const auto& neighbor : neighbors) {
        if (visited.find(neighbor->getName()) == visited.end()) {
            if (dfs(neighbor, target, visited, path)) {
                return true;
            }
        }
    }

    path.pop_back();
    return false;
}
