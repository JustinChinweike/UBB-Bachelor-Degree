#pragma once
#include "Command.h"
#include "Controller.h"



class UpdateCommand : public Command
{
private:
	Controller& controller;
	TrenchCoat oldTrenchCoat;
	TrenchCoat newTrenchCoat;


public:
	UpdateCommand(Controller& controller , const TrenchCoat& oldTrenchCoat, 
		const TrenchCoat& newTrenchCoat ) : controller{ controller }, 
		oldTrenchCoat{ oldTrenchCoat }, newTrenchCoat{ newTrenchCoat } {}



public:
	void execute() override {
		controller.updateTrenchCoat(oldTrenchCoat.getTrenchID(),
			newTrenchCoat.getTrenchID(),
			newTrenchCoat.getTrenchSize(),
			newTrenchCoat.getTrenchColour(),
			newTrenchCoat.getTrenchPrice(),
			newTrenchCoat.getTrenchQuantity(),
			newTrenchCoat.getTrenchPhotographyLink());
	}



	
	void undo() override {
		controller.updateTrenchCoat(oldTrenchCoat.getTrenchID(),
			oldTrenchCoat.getTrenchID(),
			oldTrenchCoat.getTrenchSize(),
			oldTrenchCoat.getTrenchColour(),
			oldTrenchCoat.getTrenchPrice(),
			oldTrenchCoat.getTrenchQuantity(),
			oldTrenchCoat.getTrenchPhotographyLink());
	}



	void redo() override {
		execute();
	}
};

