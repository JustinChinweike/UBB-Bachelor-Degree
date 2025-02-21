
#pragma once
#include "Command.h"
#include "Domain.h"
#include <Controller.h>



class AddCommand : public Command {
private:
    std::shared_ptr<Controller> controller;

    //Controller& controller;
    TrenchCoat trenchCoat;

public:
    AddCommand(std::shared_ptr<Controller> controller, const TrenchCoat& trenchCoat)
        : controller(controller), trenchCoat(trenchCoat) {}

    void execute() override {
        controller->addTrenchCoat(trenchCoat.getTrenchID(),
            trenchCoat.getTrenchSize(),
            trenchCoat.getTrenchColour(),
            trenchCoat.getTrenchPrice(),
            trenchCoat.getTrenchQuantity(),
            trenchCoat.getTrenchPhotographyLink());
    }

    void undo() override {
        controller->removeTrenchCoat(trenchCoat.getTrenchID());
    }


    void redo() override {
		execute();
	}
};


