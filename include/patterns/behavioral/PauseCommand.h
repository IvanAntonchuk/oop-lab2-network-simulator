#ifndef PAUSECOMMAND_H
#define PAUSECOMMAND_H

#include "SimulationCommand.h"

class PauseCommand : public SimulationCommand {
public:
    std::string execute() override;
};

#endif // PAUSECOMMAND_H
