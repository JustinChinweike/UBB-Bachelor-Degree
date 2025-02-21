#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include "Controller.h"
#include <QPushButton>

class AdminWindow : public QWidget {
    Q_OBJECT


signals:
    void backButtonClicked();


public:
    explicit AdminWindow(Controller& controller, QWidget* parent = nullptr);

private slots:
    void addTrenchCoat();
    void removeTrenchCoat();
    void updateTrenchCoat();
	void writeToDatabase();
	void readfromDatabase();


private:
    Controller& controller;
    QTableWidget* table;
    QLineEdit* idInput;
    QLineEdit* sizeInput;
    QLineEdit* colorInput;
    QLineEdit* priceInput;
    QLineEdit* quantityInput;
    QLineEdit* photoInput;
    



	


    void setupUI();
    void populateTable();
};

#endif // ADMINWINDOW_H
