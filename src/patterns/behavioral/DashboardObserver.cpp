#include "DashboardObserver.h"
#include "Subnet.h"
#include "NodeIterator.h"

DashboardObserver::DashboardObserver(std::shared_ptr<Subnet>* netPtr) : networkPtr(netPtr) {}

std::string DashboardObserver::update(const std::string& event) {
    if (event != "NETWORK_CHANGED" || !(*networkPtr)) {
        return "";
    }

    int totalNodes = 0;
    int onlineNodes = 0;
    int offlineNodes = 0;

    auto iterator = (*networkPtr)->createIterator();
    while (iterator->hasNext()) {
        auto node = iterator->next();
        totalNodes++;
        if (node->isOperational()) {
            onlineNodes++;
        } else {
            offlineNodes++;
        }
    }

    std::string stats = "Kyiv Network Stats | Total: " + std::to_string(totalNodes) +
                        " | Online: " + std::to_string(onlineNodes) +
                        " | Offline: " + std::to_string(offlineNodes);

    return stats;
}
