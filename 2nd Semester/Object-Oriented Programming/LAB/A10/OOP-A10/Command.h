#pragma once
class Command
{
	public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual void redo() = 0;

	virtual ~Command() = default;
};


