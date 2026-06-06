#include "HistoryManager.h"

HistoryManager::HistoryManager(SimulationManager* simManager) : manager(simManager) {}

void HistoryManager::executeCommand(std::unique_ptr<ICommand> command) {
    command->execute();
    undoStack.push(std::move(command));
    while (!redoStack.empty()) {
        redoStack.pop();
    }
}

void HistoryManager::undo() {
    if (undoStack.empty()) {
        return;
    }
    std::unique_ptr<ICommand> command = std::move(undoStack.top());
    undoStack.pop();
    command->undo();
    redoStack.push(std::move(command));
}

void HistoryManager::redo() {
    if (redoStack.empty()) {
        return;
    }
    std::unique_ptr<ICommand> command = std::move(redoStack.top());
    redoStack.pop();
    command->execute();
    undoStack.push(std::move(command));
}
