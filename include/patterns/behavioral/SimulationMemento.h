#ifndef SIMULATIONMEMENTO_H
#define SIMULATIONMEMENTO_H

#include <string>

class SimulationMemento {
private:
    std::string savedTopologyState;
    double savedTime;

public:
    SimulationMemento(const std::string& state, double time);

    std::string getState() const;
    double getTime() const;
};

#endif
