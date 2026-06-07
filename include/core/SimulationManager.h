#ifndef SIMULATIONMANAGER_H
#define SIMULATIONMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "SimulationObserver.h"

class HistoryManager;

/**
 * @brief Global access point for managing simulation events and history (Singleton pattern).
 * * Coordinates UI updates by notifying observers when the network changes,
 * and holds the HistoryManager for Undo/Redo functionality.
 */
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

    /** @brief Retrieves the single instance of the SimulationManager. */
    static SimulationManager& getInstance();

    void attach(std::shared_ptr<SimulationObserver> observer);
    std::string notifyObservers(const std::string& event);

    bool getIsRunning() const;
    void setRunning(bool state);

    HistoryManager* getHistory();
};

#endif
