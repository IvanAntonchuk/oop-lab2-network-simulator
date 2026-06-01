#ifndef SIMULATIONCOMMAND_H
#define SIMULATIONCOMMAND_H

#include <string>

class SimulationCommand {
public:
    virtual ~SimulationCommand() = default;
    virtual std::string execute() = 0;
};

#endif // SIMULATIONCOMMAND_H
