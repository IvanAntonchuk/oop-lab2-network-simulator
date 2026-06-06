#include "SimulationMemento.h"

SimulationMemento::SimulationMemento(const std::map<VisualNode*, std::shared_ptr<ServerNode>>& nodesState)
    : state(nodesState) {}

std::map<VisualNode*, std::shared_ptr<ServerNode>> SimulationMemento::getState() const {
    return state;
}
