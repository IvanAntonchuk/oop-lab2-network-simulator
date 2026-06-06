#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <stack>
#include <memory>
#include "SimulationCommand.h"

class SimulationManager;

class HistoryManager {
public:
    HistoryManager(SimulationManager* simManager);
    void executeCommand(std::unique_ptr<ICommand> command);
    void undo();
    void redo();

private:
    SimulationManager* manager;
    std::stack<std::unique_ptr<ICommand>> undoStack;
    std::stack<std::unique_ptr<ICommand>> redoStack;
};

#endif
