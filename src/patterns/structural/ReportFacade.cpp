#include "ReportFacade.h"

ReportFacade::ReportFacade(std::shared_ptr<NetworkNode> net) : network(net) {}

std::string ReportFacade::generateNetworkReport() {
    std::string report = "=== Network Simulation Report ===\n";

    bool isRunning = SimulationManager::getInstance().getIsRunning();
    report += "Simulation Status: " + std::string(isRunning ? "RUNNING" : "PAUSED") + "\n";

    if (network) {
        report += "Target Network: " + network->getName() + "\n";
        report += "Traffic Log:\n";
        report += network->processTraffic();
    } else {
        report += "Error: No network provided for the report.\n";
    }

    report += "=================================\n";
    return report;
}
