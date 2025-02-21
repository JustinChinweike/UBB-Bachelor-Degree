#ifndef TRENCHCOATGUI_H
#define TRENCHCOATGUI_H

#include <QWidget>
#include "Controller.h"
#include <QStandardItemModel>
#include <QTableView>
#include <QPushButton>
#include <QPushButton>

class TrenchCoatGUI : public QWidget {
    Q_OBJECT

public:
    TrenchCoatGUI(Controller& controller, QWidget* parent = nullptr);

public slots:
    void adminMode();
    void userMode();
    void browseTrenchCoats();
    void viewShoppingBasket();
    void clearLayout();

private:
    QPushButton* adminButton;
    QPushButton* userButton;
    QTableView* tableView;
    QStandardItemModel* model;
    QPushButton* viewBasketButton;
    Controller controller;
};

#endif // TRENCHCOATGUI_H
