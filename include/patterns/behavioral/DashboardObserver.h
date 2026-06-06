#ifndef DASHBOARDOBSERVER_H
#define DASHBOARDOBSERVER_H

#include "SimulationObserver.h"
#include <memory>
#include <string>

class Subnet;

class DashboardObserver : public SimulationObserver {
public:
    explicit DashboardObserver(std::shared_ptr<Subnet>* netPtr);
    std::string update(const std::string& event) override;

private:
    std::shared_ptr<Subnet>* networkPtr;
};

#endif
