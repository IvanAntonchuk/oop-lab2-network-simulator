#ifndef SIMULATIONOBSERVER_H
#define SIMULATIONOBSERVER_H

#include <string>

class SimulationObserver {
public:
    virtual ~SimulationObserver() = default;
    virtual std::string update(const std::string& event) = 0;
};

#endif
