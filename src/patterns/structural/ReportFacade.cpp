#include "ReportFacade.h"
#include "ServerNode.h"
#include "SimulationManager.h"
#include "Subnet.h"

ReportFacade::ReportFacade(std::shared_ptr<NetworkNode> net) : network(net) {}

std::vector<std::vector<std::shared_ptr<NetworkNode>>> ReportFacade::getCalculatedPaths() const {
    return calculatedPaths;
}

std::string ReportFacade::generateNetworkReport() {
    calculatedPaths.clear();
    std::string report = "=== Network Simulation Report ===\n";

    bool isRunning = SimulationManager::getInstance().getIsRunning();
    report += "Simulation Status: " + std::string(isRunning ? "RUNNING" : "PAUSED") + "\n";

    if (!network) {
        report += "Error: No network provided for the report.\n=================================\n";
        return report;
    }

    report += "Target Network: " + network->getName() + "\n";
    report += "Routing Paths & Connectivity Matrix:\n";

    auto subnet = std::dynamic_pointer_cast<Subnet>(network);
    if (subnet) {
        std::vector<std::shared_ptr<NetworkNode>> routers;
        for (auto& n : subnet->getNodes()) {
            if (n->getName().find("Router") != std::string::npos) {
                routers.push_back(n);
            }
        }

        if (!routers.empty()) {
            for (auto& node : subnet->getNodes()) {
                auto serverNode = std::dynamic_pointer_cast<ServerNode>(node);

                if (serverNode && serverNode->getStrategy()) {
                    bool isReachableFromAnyRouter = false;

                    for (auto& router : routers) {
                        auto path = serverNode->getStrategy()->calculatePath(router, node);

                        if (!path.empty()) {
                            calculatedPaths.push_back(path);
                            report += "  [Path] " + router->getName() + " -> " + node->getName() + ": ";

                            for (size_t i = 0; i < path.size(); ++i) {
                                report += path[i]->getName() + (i == path.size() - 1 ? "" : " -> ");
                            }
                            report += "\n";
                            isReachableFromAnyRouter = true;
                        }
                    }

                    if (!isReachableFromAnyRouter) {
                        report += "  [Warning] " + node->getName() + " is UNREACHABLE from all entry routers.\n";
                    }
                }
            }
        } else {
            report += "  [Critical] No core routers detected in this topology configuration.\n";
        }
    }

    report += "\nTraffic Log Details:\n";
    report += network->processTraffic();

    report += "=================================\n";
    return report;
}
