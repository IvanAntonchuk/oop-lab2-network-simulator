#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <string>

class SimulationManager {
private:
    bool isRunning;

    SimulationManager();
    ~SimulationManager() = default;

public:
    SimulationManager(const SimulationManager&) = delete;
    SimulationManager& operator=(const SimulationManager&) = delete;

    static SimulationManager& getInstance();

    std::string startSimulation();
    std::string pauseSimulation();

    bool getIsRunning() const;
};

#endif // SIMULATIONMANAGER_H
