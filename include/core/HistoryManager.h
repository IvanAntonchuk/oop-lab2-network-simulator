#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <stack>
#include <memory>
#include "SimulationCommand.h"

class SimulationManager;

/**
 * @brief Manages the execution and history of user commands (Command & Memento patterns).
 * * Provides the ability to undo and redo actions in the network editor.
 */
class HistoryManager {
public:
    HistoryManager(SimulationManager* simManager);

    /**
     * @brief Executes a new command and saves it to the undo history.
     */
    void executeCommand(std::unique_ptr<ICommand> command);

    /** @brief Reverts the last executed command. */
    void undo();

    /** @brief Re-applies the last reverted command. */
    void redo();

private:
    SimulationManager* manager;
    std::stack<std::unique_ptr<ICommand>> undoStack;
    std::stack<std::unique_ptr<ICommand>> redoStack;
};

#endif
