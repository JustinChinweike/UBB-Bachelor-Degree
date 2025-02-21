// TrenchCoatGUI.h
#pragma once
#include <QWidget>
#include <QTableView>
#include <QPushButton>
#include "Controller.h"
#include "TrenchCoatTableModel.h"


class TrenchCoatGUI : public QWidget {
    Q_OBJECT

private:
    Controller& controller;
    QTableView* tableView;
    TrenchCoatTableModel* model;
    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QPushButton* writeToDatabaseButton;



    void setupUI();
    void connectSignalsSlots();
    


private slots:

    void handleAdd();
    void handleRemove(); 
    void handleUpdate();
    void handleUndo();
    void handleRedo();
    void handlewriteToDatabase(); 


public:
    explicit TrenchCoatGUI(Controller& controller, QWidget* parent = nullptr);
    ~TrenchCoatGUI();
};

