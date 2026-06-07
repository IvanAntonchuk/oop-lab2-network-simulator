#ifndef DASHBOARDOBSERVER_H
#define DASHBOARDOBSERVER_H

#include "SimulationObserver.h"
#include <memory>
#include <string>

class Subnet;

/**
 * @brief Concrete observer that updates the UI dashboard (Observer pattern).
 * * Reacts to events from the SimulationManager and calculates real-time statistics.
 */
class DashboardObserver : public SimulationObserver {
public:
    explicit DashboardObserver(std::shared_ptr<Subnet>* netPtr);
    std::string update(const std::string& event) override;

private:
    std::shared_ptr<Subnet>* networkPtr;
};

#endif
