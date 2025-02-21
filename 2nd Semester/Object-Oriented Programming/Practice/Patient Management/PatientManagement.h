#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PatientManagement.h"

class PatientManagement : public QMainWindow
{
    Q_OBJECT

public:
    PatientManagement(QWidget *parent = nullptr);
    ~PatientManagement();

private:
    Ui::PatientManagementClass ui;
};
