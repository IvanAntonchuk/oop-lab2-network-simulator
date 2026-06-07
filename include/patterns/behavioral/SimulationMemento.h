#ifndef SIMULATIONMEMENTO_H
#define SIMULATIONMEMENTO_H

#include <map>
#include <memory>

class VisualNode;
class ServerNode;

/**
 * @brief Captures and stores the internal state of the simulation (Memento pattern).
 * * Used by the HistoryManager to save snapshots of the network state.
 */
class SimulationMemento {
public:
    SimulationMemento(const std::map<VisualNode*, std::shared_ptr<ServerNode>>& nodesState);
    std::map<VisualNode*, std::shared_ptr<ServerNode>> getState() const;
private:
    std::map<VisualNode*, std::shared_ptr<ServerNode>> state;
};

#endif
