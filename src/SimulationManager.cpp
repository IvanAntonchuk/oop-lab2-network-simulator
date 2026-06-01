#include "SimulationManager.h"

SimulationManager::SimulationManager() : isRunning(false) {}

SimulationManager& SimulationManager::getInstance() {
    static SimulationManager instance;
    return instance;
}

std::string SimulationManager::startSimulation() {
    if (isRunning) {
        return "[Manager] Симуляція вже запущена.\n";
    }
    isRunning = true;
    return "[Manager] СТАРТ: Симуляцію успішно запущено.\n";
}

std::string SimulationManager::pauseSimulation() {
    if (!isRunning) {
        return "[Manager] Симуляція вже на паузі або не запущена.\n";
    }
    isRunning = false;
    return "[Manager] ПАУЗА: Симуляцію зупинено.\n";
}

bool SimulationManager::getIsRunning() const {
    return isRunning;
}
