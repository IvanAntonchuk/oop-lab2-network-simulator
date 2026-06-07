#ifndef SIMULATIONCOMMAND_H
#define SIMULATIONCOMMAND_H

#include <string>

/**
 * @brief Interface for encapsulating requests as objects (Command pattern).
 * * Defines the standard structure for any action that can be executed and undone.
 */
class ICommand {
public:
    virtual ~ICommand() = default;

    /** @brief Executes the command's primary logic. */
    virtual void execute() = 0;

    /** @brief Reverts the effects of the command. */
    virtual void undo() = 0;
};

#endif
