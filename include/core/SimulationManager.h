#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "SimulationObserver.h"

class HistoryManager;

class SimulationManager {
private:
    bool isRunning;
    std::vector<std::shared_ptr<SimulationObserver>> observers;
    std::unique_ptr<HistoryManager> history;

    SimulationManager();
    ~SimulationManager();

public:
    SimulationManager(const SimulationManager&) = delete;
    SimulationManager& operator=(const SimulationManager&) = delete;

    static SimulationManager& getInstance();

    void attach(std::shared_ptr<SimulationObserver> observer);
    std::string notifyObservers(const std::string& event);

    bool getIsRunning() const;
    void setRunning(bool state);

    HistoryManager* getHistory();
};

#endif
