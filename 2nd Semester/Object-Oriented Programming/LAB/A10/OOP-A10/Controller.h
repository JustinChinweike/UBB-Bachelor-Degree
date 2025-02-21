#pragma once
#include <string>
#include <vector>
#include "Repository.h"
#include <CommandManager.h>


class Controller {
private:
    Repository repository;
    Repository shoppingBasket;
    CommandManager commandManager;


    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;



public:
    Controller();
    explicit Controller(const Repository& repository);

    bool addTrenchCoat(int trenchID,
        int trenchSize,
        const std::string& trenchColour,
        float trenchPrice,
        int trenchQuantity,
        const std::string& trenchPhotograph);

    bool removeTrenchCoat(int trenchID);
    bool updateTrenchCoat(int trenchID,
        int trenchNewID,
        int trenchSize,
        const std::string& trenchColour,
        float trenchPrice,
        int trenchQuantity,
        const std::string& trenchPhotograph);


    bool addTrenchCoatToShoppingBasket(int trenchID);


    int trenchCoatExists(int trenchID);





    TrenchCoat getTrenchCoat(int trenchID);
    std::vector<TrenchCoat> getAllTrenchCoats();


    std::vector<TrenchCoat> getShoppingBasketTrenchCoats();


    std::vector<TrenchCoat> filterBySize(int trenchSize);
  
    int getSize();  
    void setFileName(std::string newFileName);
    std::string getFileName() const;

    void saveProgress();
    void loadFromFile();

    void clearShoppingBasket();

    

    // Undo/Redo operations
    void undo();
    void redo();
}; 