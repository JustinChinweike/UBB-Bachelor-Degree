#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_GUI2.h"

class GUI2 : public QMainWindow
{
    Q_OBJECT

public:
    GUI2(QWidget *parent = nullptr);
    ~GUI2();

private:
    Ui::GUI2Class ui;
};
