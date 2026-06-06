#include "ShortestPathStrategy.h"
#include "NetworkNode.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

std::string ShortestPathStrategy::getName() const {
    return "Shortest Path (OSPF / BFS)";
}

std::vector<std::shared_ptr<NetworkNode>> ShortestPathStrategy::calculatePath(
    std::shared_ptr<NetworkNode> source,
    std::shared_ptr<NetworkNode> destination) {

    std::vector<std::shared_ptr<NetworkNode>> path;
    if (!source || !destination) return path;

    std::queue<std::shared_ptr<NetworkNode>> q;
    std::unordered_map<std::string, std::shared_ptr<NetworkNode>> parentMap;
    std::unordered_set<std::string> visited;

    q.push(source);
    visited.insert(source->getName());
    parentMap[source->getName()] = nullptr;

    bool found = false;

    while (!q.empty()) {
        auto current = q.front();
        q.pop();

        if (current->getName() == destination->getName()) {
            found = true;
            break;
        }

        for (const auto& neighbor : current->getConnections()) {
            if (visited.find(neighbor->getName()) == visited.end()) {
                visited.insert(neighbor->getName());
                parentMap[neighbor->getName()] = current;
                q.push(neighbor);
            }
        }
    }

    if (found) {
        auto curr = destination;
        while (curr != nullptr) {
            path.push_back(curr);
            curr = parentMap[curr->getName()];
        }
        std::reverse(path.begin(), path.end());
    }

    return path;
}
