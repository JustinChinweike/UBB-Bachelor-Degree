#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include "Controller.h"
#include <QPushButton>
#include <QTableView>
#include <TrenchCoatTableModel.h>
#include <QMessageBox>

class AdminWindow : public QWidget {
    Q_OBJECT


signals:
    void backButtonClicked();


public:
    std::vector<TrenchCoat> trenchCoats;


    explicit AdminWindow(Controller& controller, QWidget* parent = nullptr);

private slots:

    void addTrenchCoat();
    void removeTrenchCoat();
    void updateTrenchCoat();
	void writeToDatabase();
	void readfromDatabase();


private slots:
    void undo() {
        try {
            controller.undo();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }

    void redo() {
        try {
            controller.redo();
        }
        catch (const std::exception& e) {
            QMessageBox::warning(this, "Error", e.what());
        }
    }



private:
    Controller& controller;
    QTableView* tableView;
    QLineEdit* idInput;
    QLineEdit* sizeInput;
    QLineEdit* colorInput;
    QLineEdit* priceInput;
    QLineEdit* quantityInput;
    QLineEdit* photoInput;

    TrenchCoatTableModel* model;

    QPushButton* undoButton;
    QPushButton* redoButton;
    



	


    void setupUI();
    void populateTable();
};

#endif // ADMINWINDOW_H
