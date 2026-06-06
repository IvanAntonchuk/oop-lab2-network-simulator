#include "SimulationManager.h"
#include "HistoryManager.h"

SimulationManager::SimulationManager()
    : isRunning(false), history(std::make_unique<HistoryManager>(this)) {}

SimulationManager::~SimulationManager() = default;

SimulationManager& SimulationManager::getInstance() {
    static SimulationManager instance;
    return instance;
}

void SimulationManager::attach(std::shared_ptr<SimulationObserver> observer) {
    if (observer) {
        observers.push_back(observer);
    }
}

std::string SimulationManager::notifyObservers(const std::string& event) {
    std::string log;
    for (const auto& obs : observers) {
        log += obs->update(event);
    }
    return log;
}

bool SimulationManager::getIsRunning() const {
    return isRunning;
}

void SimulationManager::setRunning(bool state) {
    isRunning = state;
}

HistoryManager* SimulationManager::getHistory() {
    return history.get();
}
