#include "SimulationManager.h"

SimulationManager::SimulationManager()
    : isRunning(false), currentTopologyState("Initial"), currentTime(0.0) {}

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

std::string SimulationManager::startSimulation() {
    if (isRunning) {
        return "[Manager] Simulation is already running.\n";
    }
    isRunning = true;
    std::string res = "[Manager] START: Simulation successfully started.\n";
    res += notifyObservers("SIMULATION_STARTED");
    return res;
}

std::string SimulationManager::pauseSimulation() {
    if (!isRunning) {
        return "[Manager] Simulation is already paused or not running.\n";
    }
    isRunning = false;
    std::string res = "[Manager] PAUSE: Simulation stopped.\n";
    res += notifyObservers("SIMULATION_PAUSED");
    return res;
}

bool SimulationManager::getIsRunning() const {
    return isRunning;
}

void SimulationManager::setTopologyState(const std::string& state) {
    currentTopologyState = state;
}

void SimulationManager::setTime(double time) {
    currentTime = time;
}

std::unique_ptr<SimulationMemento> SimulationManager::saveState() const {
    return std::make_unique<SimulationMemento>(currentTopologyState, currentTime);
}

void SimulationManager::restoreState(std::unique_ptr<SimulationMemento> memento) {
    if (memento) {
        currentTopologyState = memento->getState();
        currentTime = memento->getTime();
    }
}

std::string SimulationManager::getCurrentStateInfo() const {
    return "Topology: " + currentTopologyState + " | Time: " + std::to_string(currentTime);
}
