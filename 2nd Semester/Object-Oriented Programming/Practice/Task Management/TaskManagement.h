#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TaskManagement.h"

class TaskManagement : public QMainWindow
{
    Q_OBJECT

public:
    TaskManagement(QWidget *parent = nullptr);
    ~TaskManagement();

private:
    Ui::TaskManagementClass ui;
};
