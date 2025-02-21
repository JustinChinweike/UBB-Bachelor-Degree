#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include "Controller.h"
#include <QLabel>

class UserWindow : public QWidget {
    Q_OBJECT

public:
    explicit UserWindow(Controller& controller, QWidget* parent = nullptr);


signals:
	void backButtonClicked();

private slots:
    void nextTrenchCoat();
	void cycleThroughTrenchCoats();
	void addTrenchCoatToShoppingBasket();
	void removeTrenchCoatFromShoppingBasket();
	void printShoppingBasket();
	void emptyBasketOfTrenchCoats();
	void displayShoppingBasket();
	void saveShoppingBasketToFile();


	void updateTrenchCoatDetails(); 

 
    void showTrenchCoatDetails(int index);

private:
    Controller& controller;


    QTableWidget* table;
	std::vector<TrenchCoat> trenchCoats;
    QLabel* trenchDetails;
    int currentIndex;
	int totalCost; 

	/*QPushButton* cycleButton;
	QPushButton* addToBasketButton;
	QPushButton* removeFromBasketButton;
	QPushButton* printBasketButton;
	QPushButton* emptyBasketButton;
	QPushButton* displayBasketButton;
	QPushButton* saveBasketButton;*/


    void setupUI();
    void populateTable();
};

#endif // USERWINDOW_H
