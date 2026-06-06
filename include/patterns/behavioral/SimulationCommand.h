#ifndef SIMULATIONCOMMAND_H
#define SIMULATIONCOMMAND_H

#include <string>

class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

#endif
