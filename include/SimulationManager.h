#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "SimulationObserver.h"

class SimulationManager {
private:
    bool isRunning;
    std::vector<std::shared_ptr<SimulationObserver>> observers;

    SimulationManager();
    ~SimulationManager() = default;

public:
    SimulationManager(const SimulationManager&) = delete;
    SimulationManager& operator=(const SimulationManager&) = delete;

    static SimulationManager& getInstance();

    void attach(std::shared_ptr<SimulationObserver> observer);
    std::string notifyObservers(const std::string& event);

    std::string startSimulation();
    std::string pauseSimulation();

    bool getIsRunning() const;
};

#endif
