//#include "TrenchCoatGUI.h"
//#include <QtWidgets/QApplication>
//#include "Controller.h"
//
//
//int main(int argc, char* argv[])
//{
//    QApplication app(argc, argv);
//    Controller controller ("default.txt");
//    
//    TrenchCoatGUI w(controller); // Pass the Controller object to the TrenchCoatGUI constructor
//    w.show();
//    return app.exec();
//}



// Main.cpp
#include "Repository.h"
#include "Controller.h"
#include <fstream>

#include <QtWidgets/QApplication>
#include "TrenchCoatGUI.h"



int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	// Create repository and controller 
	Repository repository("default.txt");
	Repository shoppingBasket("basket.txt");

	Controller controller(repository);

	// Create and show main window
	TrenchCoatGUI w(controller);
	w.show();

	return app.exec();
}









