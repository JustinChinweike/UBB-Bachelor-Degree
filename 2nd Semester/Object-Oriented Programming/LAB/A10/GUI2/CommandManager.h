#pragma once
#include "Command.h"
#include <vector>
#include <memory>
#include <exception>
#include <stdexcept>

class CommandManager {
private:
    std::vector<std::shared_ptr<Command>> commandHistory;
    int currentCommandIndex = -1;

public:
    void executeCommand(std::shared_ptr<Command> command) {
        // If we are not at the end of the history, remove the "future" commands
        if (currentCommandIndex != commandHistory.size() - 1) {
            commandHistory.erase(commandHistory.begin() + currentCommandIndex + 1, commandHistory.end());
        }

        command->execute();
        commandHistory.push_back(command);
        currentCommandIndex++;
    }

    void undo() {
        if (currentCommandIndex >= 0) {
            commandHistory[currentCommandIndex]->undo();
            currentCommandIndex--;
        }
        else {
            throw std::runtime_error("No more undos available");
        }
    }

    void redo() {
        if (currentCommandIndex < commandHistory.size() - 1) {
            currentCommandIndex++;
            commandHistory[currentCommandIndex]->redo();
        }
        else {
            throw std::runtime_error("No more redos available");
        }
    }
};
