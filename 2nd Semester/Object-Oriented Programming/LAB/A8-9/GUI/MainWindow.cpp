#include "MainWindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(Controller& controller, QWidget* parent)
    : QMainWindow(parent), controller(controller), adminWindow(nullptr), userWindow(nullptr) {
    QWidget* centralWidget = new QWidget(this);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);


    adminWindow = new AdminWindow(controller);
    connect(adminWindow, &AdminWindow::backButtonClicked, this, &MainWindow::show);

    userWindow = new UserWindow(controller);
    connect(userWindow, &UserWindow::backButtonClicked, this, &MainWindow::show);


    // Create a QFont object
    QFont windowFont("Arial", 20);  // Change "Arial" to your preferred font and "20" to your preferred size

    // Set the font of the window
    this->setFont(windowFont);


    QPushButton* adminButton = new QPushButton("Admin Mode", this);
    QPushButton* userButton = new QPushButton("User Mode", this);

    layout->addWidget(adminButton);
    layout->addWidget(userButton);

    connect(adminButton, &QPushButton::clicked, this, &MainWindow::openAdminMode);
    connect(userButton, &QPushButton::clicked, this, &MainWindow::openUserMode);

    setCentralWidget(centralWidget);
}


void MainWindow::openAdminMode() {
    if (!adminWindow) {
        adminWindow = new AdminWindow(controller);
    }
    adminWindow->show();
}




void MainWindow::openUserMode() {
    if (!userWindow) {
        userWindow = new UserWindow(controller);
    }
    userWindow->show();
}





