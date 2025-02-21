#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Controller.h"
#include "AdminWindow.h"
#include "UserWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Controller& controller, QWidget* parent = nullptr);

private:
    Controller& controller;
    AdminWindow* adminWindow;
    UserWindow* userWindow;

private slots:
    void openAdminMode();
    void openUserMode();
};

#endif // MAINWINDOW_H
