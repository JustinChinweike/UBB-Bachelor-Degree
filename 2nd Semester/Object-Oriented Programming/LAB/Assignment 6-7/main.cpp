
// Main.cpp
#include "UI.h"
#include "Repository.h"
#include "Controller.h"
#include "TestAll.h"

int main()
{
    testDomain();
    //testRepository();
    //testController();

    // Create the repository and read data from file
    Repository basket_repository("basket.txt");
    basket_repository.readFromFile();

    // Create controllers using the repository
    Controller controller;
    Controller basket_controller(basket_repository);

    // Create UI and run application
    UI ui(controller, basket_controller);
    ui.runApplication();

    // Write modified data back to file before exiting
    basket_repository.writeToFile();

    return 0;
}













//// Main.cpp
//#include "UI.h"
//#include "Repository.h"
//#include "Controller.h"
//#include "TestAll.h"
//
//int main()
//{
//    testDomain();
//    //testRepository();
//    testController();
//    {
//        Controller controller;
//        Repository basket_repository("basket.txt");
//        Controller basket_controller(basket_repository);
//
//        UI ui(controller, basket_controller);
//        ui.runApplication();
//    }
//
//
//
//    return 0;
//}
