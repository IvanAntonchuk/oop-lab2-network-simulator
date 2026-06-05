#include "SimulationMemento.h"

SimulationMemento::SimulationMemento(const std::string& state, double time)
    : savedTopologyState(state), savedTime(time) {}

std::string SimulationMemento::getState() const {
    return savedTopologyState;
}

double SimulationMemento::getTime() const {
    return savedTime;
}
