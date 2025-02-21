
// Main.cpp
#include "UI.h"
#include "Repository.h"
#include "Controller.h"
#include <fstream>

#include <QtWidgets/QApplication>
#include <MainWindow.h>

int main(int argc, char* argv[])
{  
	QApplication app(argc, argv);

	// Create repository and controller 
	Repository repository("default.txt");
	Repository shoppingBasket("basket.txt");

    Controller controller(repository);

	// Create and show main window
	MainWindow mainWindow(controller); 
	mainWindow.show(); 

	return app.exec();
}








	