#ifndef STARTCOMMAND_H
#define STARTCOMMAND_H

#include "SimulationCommand.h"

class StartCommand : public SimulationCommand {
public:
    std::string execute() override;
};

#endif // STARTCOMMAND_H
