#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "SimulationObserver.h"
#include "SimulationMemento.h"

class SimulationManager {
private:
    bool isRunning;
    std::vector<std::shared_ptr<SimulationObserver>> observers;

    std::string currentTopologyState;
    double currentTime;

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

    void setTopologyState(const std::string& state);
    void setTime(double time);

    std::unique_ptr<SimulationMemento> saveState() const;
    void restoreState(std::unique_ptr<SimulationMemento> memento);

    std::string getCurrentStateInfo() const;
};

#endif
