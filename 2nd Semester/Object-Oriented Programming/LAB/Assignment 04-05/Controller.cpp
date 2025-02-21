#include "Controller.h"

using namespace std;

Controller::Controller()
{
    this->repository = Repository();
}

Controller::Controller(Repository repository)
{
    this->repository = repository;
}

bool Controller::addTrenchCoat(int trenchID,
    int trenchSize,
    std::string trenchColour,
    int trenchPrice,
    int trenchQuantity,
    std::string trenchPhotograph)
{

    for (int i = 0; i < this->repository.getSize(); i++)
        if (this->repository.getAllTrenchCoats()[i].getTrenchID() == trenchID) {
            return false;
        }

    this->repository.addTrenchCoat(trenchID,
        trenchSize,
        trenchColour,
        trenchPrice,
        trenchQuantity,
        trenchPhotograph);
    return true;

}

void Controller::removeTrenchCoat(int trenchID)
{
    this->repository.removeTrenchCoat(trenchID);
}

bool Controller::updateTrenchCoat(int trenchID,
    int trenchNewID,
    int trenchSize,
    std::string trenchColour,
    int trenchPrice,
    int trenchQuantity,
    std::string trenchPhotograph)
{
    if (!this->trenchCoatExists(trenchID)) {
        return false;
    }
    else {
        this->repository.updateTrenchCoat(trenchID,
            trenchNewID,
            trenchSize,
            trenchColour,
            trenchPrice,
            trenchQuantity,
            trenchPhotograph);
        return true;
    }
}

int Controller::trenchCoatExists(int trenchID)
{
    int counter = 0;
    for (int i = 0; i < this->repository.getSize(); i++)
        if (this->repository.getAllTrenchCoats()[i].getTrenchID() == trenchID) {
            counter++;
        }
    return counter;
}

TrenchCoat Controller::getTrenchCoat(int trenchID)
{
    return this->repository.getTrenchCoat(trenchID);

}

dynamicVector<TrenchCoat> Controller::getAllTrenchCoats()
{
    return this->repository.getAllTrenchCoats();
}

dynamicVector<TrenchCoat> Controller::filterBySize(int trenchSize)
{

    dynamicVector<TrenchCoat> filteredTrenchCoats;
    dynamicVector<TrenchCoat> allTrenchCoats = this->repository.getAllTrenchCoats();

    for (int i = 0; i < this->repository.getSize(); i++)
        if (allTrenchCoats[i].getTrenchSize() == trenchSize)
            filteredTrenchCoats.append(allTrenchCoats[i]);

    return filteredTrenchCoats;
}

int Controller::getSize()
{
    return this->repository.getSize();
}

void Controller::setFileName(std::string newFileName)
{
    this->repository.setFileName(newFileName);
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


void Controller::addInitialTrenchCoats() {
    // Adding ten trench coats to the system
    this->addTrenchCoat(1, 38, "Black", 99.99, 10, "black_trench.jpg");
    this->addTrenchCoat(2, 40, "Beige", 119.99, 15, "beige_trench.jpg");
    this->addTrenchCoat(3, 42, "Navy Blue", 89.99, 20, "navy_blue_trench.jpg");
    this->addTrenchCoat(4, 38, "Brown", 109.99, 12, "brown_trench.jpg");
    this->addTrenchCoat(5, 40, "Grey", 79.99, 18, "grey_trench.jpg");
    this->addTrenchCoat(6, 42, "Red", 129.99, 22, "red_trench.jpg");
    this->addTrenchCoat(7, 38, "Green", 99.99, 14, "green_trench.jpg");
    this->addTrenchCoat(8, 40, "White", 109.99, 16, "white_trench.jpg");
    this->addTrenchCoat(9, 42, "Yellow", 69.99, 25, "yellow_trench.jpg");
    this->addTrenchCoat(10, 38, "Purple", 79.99, 30, "purple_trench.jpg");
}