//Controller.cpp
#include <fstream>
#include <iostream>
#include "Controller.h"
#include "Domain.h"
#include <CommandManager.h>
#include <RemoveCommand.h>
#include <UpdateCommand.h>
#include <AddCommand.h>
#include <memory>

using namespace std;


Controller::Controller()
{
    this->repository = Repository();
	this->shoppingBasket = Repository();
    loadFromFile(); // Load data from file when controller is created

}


Controller::Controller(const Repository& repository)
{
    this->repository = repository;
}





bool Controller::addTrenchCoat(int trenchID,
    int trenchSize,
    const std::string& trenchColour,
    float trenchPrice,
    int trenchQuantity,
    const std::string& trenchPhotograph)
{
    if (this->repository.validID(trenchID))
        return false;

    TrenchCoat trenchCoat(trenchID, 
        trenchSize,
        trenchColour, 
        trenchPrice,
        trenchQuantity, 
        trenchPhotograph);
    auto cmd = std::make_shared<AddCommand>(this, trenchCoat);
    commandManager.executeCommand(cmd);
    return true;
}


/*bool Controller::addTrenchCoat(int trenchID,
    int trenchSize,
    const std::string& trenchColour,
    float trenchPrice,
    int trenchQuantity,
    const std::string& trenchPhotograph)
{
    if (this->repository.validID(trenchID))
        return false;

    return this->repository.addTrenchCoat(trenchID,
        trenchSize,
        trenchColour,
        trenchPrice,
        trenchQuantity,
        trenchPhotograph);
}*/





bool Controller::removeTrenchCoat(int trenchID)
{
    TrenchCoat trenchCoat = repository.getTrenchCoat(trenchID);
    auto cmd = std::make_shared<RemoveCommand>(this, trenchCoat);
    commandManager.executeCommand(cmd);
    return true;
}


//bool Controller::removeTrenchCoat(int trenchID)
//{
//    return this->repository.removeTrenchCoat(trenchID);
//}
//
// 
// 
//bool Controller::updateTrenchCoat(int trenchID,
//    int trenchNewID,
//    int trenchSize,
//    const std::string& trenchColour,
//    float trenchPrice,
//    int trenchQuantity,
//    const std::string& trenchPhotograph)
//{
//    return this->repository.updateTrenchCoat(trenchID,
//        trenchNewID,
//        trenchSize,
//        trenchColour,
//        trenchPrice,
//        trenchQuantity,
//        trenchPhotograph);
//}


bool Controller::updateTrenchCoat(int trenchID,
    int trenchNewID,
    int trenchSize,
    const std::string& trenchColour,
    float trenchPrice,
    int trenchQuantity,
    const std::string& trenchPhotograph)
{
    TrenchCoat oldTrenchCoat = repository.getTrenchCoat(trenchID);
    TrenchCoat newTrenchCoat(trenchNewID, trenchSize, trenchColour, trenchPrice, trenchQuantity, trenchPhotograph);
    auto cmd = std::make_shared<UpdateCommand>(this, oldTrenchCoat, newTrenchCoat);
    commandManager.executeCommand(cmd);
    return true;
}


//bool Controller::updateTrenchCoat(int trenchID,
//    int trenchNewID,
//    int trenchSize,
//    const std::string& trenchColour,
//    float trenchPrice,
//    int trenchQuantity,
//    const std::string& trenchPhotograph)
//{
//    TrenchCoat oldTrenchCoat = repository.getTrenchCoat(trenchID);
//    TrenchCoat newTrenchCoat(trenchNewID, trenchSize, trenchColour, trenchPrice, trenchQuantity, trenchPhotograph);
//    auto cmd = std::make_unique<UpdateCommand>(this, oldTrenchCoat, newTrenchCoat);
//    commandManager.executeCommand(std::move(cmd));
//    return true;
//}
//

bool Controller::addTrenchCoatToShoppingBasket(int trenchID) {
    // Check if the trench coat exists in the main repository
    if (!repository.validID(trenchID)) {
        return false;
    }

    // Get the trench coat from the main repository
    TrenchCoat trenchCoat = repository.getTrenchCoat(trenchID);

    // Add the trench coat to the shopping basket
    shoppingBasket.addTrenchCoat(trenchCoat.getTrenchID(),
        trenchCoat.getTrenchSize(),
        trenchCoat.getTrenchColour(),
        trenchCoat.getTrenchPrice(),
        1, // Assume the quantity is 1 when adding to the shopping basket
        trenchCoat.getTrenchPhotographyLink());

    return true;
}



int Controller::trenchCoatExists(int trenchID)
{
    return this->repository.validID(trenchID);
}


void Controller::executeCommand(std::shared_ptr<Command> command) {
    commandManager.executeCommand(command);
}


TrenchCoat Controller::getTrenchCoat(int trenchID)
{
    return this->repository.getTrenchCoat(trenchID);
}

std::vector<TrenchCoat> Controller::getAllTrenchCoats()
{
    return this->repository.getAllTrenchCoats();
}


std::vector<TrenchCoat> Controller::getShoppingBasketTrenchCoats() {
    return shoppingBasket.getAllTrenchCoats();
}



std::vector<TrenchCoat> Controller::filterBySize(int trenchSize)
{
    std::vector<TrenchCoat> filteredTrenchCoats;
    std::vector<TrenchCoat> allTrenchCoats = this->repository.getAllTrenchCoats();
    for (auto& trenchCoat : allTrenchCoats)
    {
        if (trenchCoat.getTrenchSize() == trenchSize)
        {
            filteredTrenchCoats.push_back(trenchCoat);
        }
    }
    return filteredTrenchCoats;
}





int Controller::getSize()
{
    return this->repository.getSize();
}

void Controller::setFileName(std::string newFileName)
{
    this->repository.setFileName(std::move(newFileName));
}

std::string Controller::getFileName() const
{
    return this->repository.getFileName();
}

void Controller::saveProgress()
{
    this->repository.writeToFile();
}

void Controller::loadFromFile()
{
    this->repository.readFromFile();
}

void Controller::clearShoppingBasket()
{
    shoppingBasket.clear();

}

void Controller::undo() {
    commandManager.undo();
}

void Controller::redo() {
    commandManager.redo();
}