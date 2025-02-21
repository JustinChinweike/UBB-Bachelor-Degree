#pragma once
#include "Command.h"
#include "Controller.h"


class RemoveCommand : public Command
{
private:
	//Controller& controller;
	
	std::shared_ptr<Controller> controller;
	TrenchCoat trenchCoat;

public:

	RemoveCommand(std::shared_ptr<Controller> controller, const TrenchCoat& trenchCoat) :
		controller{ controller }, trenchCoat{ trenchCoat } {}


	void execute() override
	{
		controller->removeTrenchCoat(trenchCoat.getTrenchID());
	}



	void undo() override
	{
		controller->addTrenchCoat
		(trenchCoat.getTrenchID(), 
			trenchCoat.getTrenchSize(), 
			trenchCoat.getTrenchColour(), 
			trenchCoat.getTrenchPrice(), 
			trenchCoat.getTrenchQuantity(), 
			trenchCoat.getTrenchPhotographyLink());
	}



	void redo() override
	{
		execute();
	}

};





