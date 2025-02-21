

//Repository.cpp
#include "Repository.h"
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

Repository::Repository(std::string FileName) {
    this->FileName = std::move(FileName);
    this->readFromFile();
}



bool Repository::addTrenchCoat(int id,
    int sizeOfTrench,
    const std::string& colourOfTrench,
    float priceOfTrench,
    int quantityOfTrench,
    const std::string& photography_linkOfTrench) {
    //Check if the ID already exists
    if (validID(id)) {
        //// Display a message indicsting that the entity already exist. 
        cout << "Trench Coat with ID " << id << ":" "Already Exist:." << endl;
        // Return false to indicate that the addition was unsuccessful
        return false;
    }

    // If the ID is unique, create the trench coat and add it to the repository. 
    TrenchCoat trenchCoat(id, sizeOfTrench, colourOfTrench, priceOfTrench,
        quantityOfTrench, photography_linkOfTrench);
    this->trenchCoats.push_back(trenchCoat);

    // Return true to indicate that the trench coat addiition was successsful.
    return true;

}



bool Repository::removeTrenchCoat(int trenchID) {
    // Find the trench coat with the specified ID using std::find_if
    auto iter = std::find_if(trenchCoats.begin(), trenchCoats.end(),
        [trenchID](const TrenchCoat& trenchCoat) { return trenchCoat.getTrenchID() == trenchID; });

    // Check if the trench coat with the specified ID was found
    if (iter != trenchCoats.end()) {
        // If found, erase the trench coat from the vector
        trenchCoats.erase(iter);
        // Return true to indicate successful removal
        return true;
    }
    // Return false if the trench coat with the specified ID was not found
    return false;
}


bool Repository::updateTrenchCoat(int trenchID,
    int newID,
    int newSizeOfTrench,
    const std::string& newColourOfTrench,
    float newPriceOfTrench,
    int newQuantityOfTrench,
    const std::string& newPhotography_linkOfTrench) {
    // Find the trench coat with the specified ID using std::find_if
    auto iter = std::find_if(trenchCoats.begin(), trenchCoats.end(),
        [trenchID](const TrenchCoat& trenchCoat) { return trenchCoat.getTrenchID() == trenchID; });

    // Check if the trench coat with the specified ID was found
    if (iter != trenchCoats.end()) {
        // Update the trench coat's attributes with the new values
        iter->setTrenchID(newID);
        iter->setTrenchSize(newSizeOfTrench);
        iter->setTrenchColour(newColourOfTrench);
        iter->setTrenchPrice(newPriceOfTrench);
        iter->setTrenchQuantity(newQuantityOfTrench);
        iter->setTrenchPhotographyLink(newPhotography_linkOfTrench);
        // Return true to indicate successful update
        return true;
    }
    // Return false if the trench coat with the specified ID was not found
    return false;
}



bool Repository::validID(int trenchID) {
    // Check if any trench coat in the repository has the specified ID
    return std::any_of(trenchCoats.begin(), trenchCoats.end(),
        [trenchID](const TrenchCoat& trenchCoat) { return trenchCoat.getTrenchID() == trenchID; });
}




//TrenchCoat Repository::getTrenchCoat(int trenchID) {
//    for (auto& trenchCoat : this->trenchCoats) {
//        if (trenchCoat.getTrenchID() == trenchID) {
//            return trenchCoat;
//        }
//    }
//    return TrenchCoat(-1, -1, "", -1, -1, "");
//}


TrenchCoat Repository::getTrenchCoat(int trenchID) {
    // Find the trench coat with the specified ID using std::find_if
    auto iter = std::find_if(trenchCoats.begin(), trenchCoats.end(),
        [trenchID](const TrenchCoat& trenchCoat) { return trenchCoat.getTrenchID() == trenchID; });

    // Check if the trench coat with the specified ID was found
    if (iter != trenchCoats.end())
        // If found, return the trench coat
        return *iter;

    // Return a default constructed trench coat if the trench coat with the specified ID was not found
    return TrenchCoat(-1, -1, "", -1, -1, "");
}



std::vector<TrenchCoat> Repository::getAllTrenchCoats() {
    // Return all trench coats in the repository
    return this->trenchCoats;
}



unsigned long int Repository::getSize() {
    return this->trenchCoats.size();
}



void Repository::setFileName(std::string newFileName) {
    this->FileName = std::move(newFileName);
}

std::string Repository::getFileName() const {
    return this->FileName;
}


void Repository::writeToFile() {
    std::ofstream file(this->FileName);
    for (auto& trenchCoat : this->trenchCoats) {
        file << trenchCoat; // Using insertion operator
    }
    file.close();
}


void Repository::readFromFile() {
    std::ifstream file(this->FileName);
    TrenchCoat trench;
    while (file >> trench) { // Using extraction operator
        this->trenchCoats.push_back(trench);
    }
    file.close();
}


void Repository::clear() {
    trenchCoats.clear();
}



Repository::Repository() {
    this->FileName = "default.txt";
}



