#pragma once
#include "Command.h"
# include <stack>
#include <memory>





class CommandManager
{
private:
	std::stack<std::unique_ptr<Command>> undoStack;
	std::stack<std::unique_ptr<Command>> redoStack;


public:

	void executeCommand(std::unique_ptr<Command> cmd) {
		cmd->execute();
		undoStack.push(std::move(cmd));

		// Clear the redo stack
		while (!redoStack.empty()) {
			redoStack.pop();
		}
	}



	void undo() {
		if (undoStack.empty()) {
			throw std::exception("No more undos");
		}

		auto cmd = std::move(undoStack.top());
		undoStack.pop();
		cmd->undo();
		redoStack.push(std::move(cmd));
	}



	void redo() {
		if (redoStack.empty()) {
			throw std::exception("No more redos");
		}

		auto cmd = std::move(redoStack.top());
		redoStack.pop();
		cmd->redo();
		undoStack.push(std::move(cmd));
	

}

	
};

