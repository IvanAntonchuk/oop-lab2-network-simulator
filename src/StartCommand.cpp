#include "StartCommand.h"
#include "SimulationManager.h"

std::string StartCommand::execute() {
    return SimulationManager::getInstance().startSimulation();
}
