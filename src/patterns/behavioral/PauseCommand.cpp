#include "PauseCommand.h"
#include "SimulationManager.h"

std::string PauseCommand::execute() {
    return SimulationManager::getInstance().pauseSimulation();
}
