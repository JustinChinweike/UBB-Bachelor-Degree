
//Repository.h
#pragma once
#include <string>
#include <vector>
#include "Domain.h"

class Repository {
private:
    std::vector<TrenchCoat> trenchCoats;
    std::string FileName;


public:
    Repository();
    Repository(std::string FileName);


    bool addTrenchCoat(int id,
        int sizeOfTrench,
        const std::string& colourOfTrench,
        float priceOfTrench,
        int quantityOfTrench,
        const std::string& photography_linkOfTrench);

    bool removeTrenchCoat(int trenchID);
    bool updateTrenchCoat(int trenchID,
        int newID,
        int newSizeOfTrench,
        const std::string& newColourOfTrench,
        float newPriceOfTrench,
        int newQuantityOfTrench,
        const std::string& newPhotography_linkOfTrench);

    bool validID(int trenchID);
    TrenchCoat getTrenchCoat(int trenchID);
    std::vector<TrenchCoat> getAllTrenchCoats();

    unsigned long int getSize();


    void setFileName(std::string newFileName);
    std::string getFileName() const;

    void writeToFile();
    void readFromFile();

    void clear();


};








